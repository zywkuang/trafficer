/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 10/28/16
**/

#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cstdio>
#include "Json.h"

#ifndef LLONG_MAX
#define LLONG_MAX 9223372036854775807LL
#endif
#ifndef LLONG_MIN
#define LLONG_MIN (-LLONG_MAX - 1LL)
#endif

static const char *global_ep;

const char *cJsonGetErrorPtr() {
    return global_ep;
}

static int cJsonStrCaseCmp(const char *s1, const char *s2) {

    if (!s1)  return (s1 == s2) ? 0 : 1;
    if (!s2)  return 1;

    for (; tolower(*s1) == tolower(*s2); s1++, s2++) {
        if (*s1 == 0)  return 0;
    }

    return tolower(*(const unsigned char *)s1) - tolower(*(const unsigned char *)s2);
}

static char* cJsonStrDup(const char* str) {
    size_t len;
    char* copy;

    len = strlen(str) + 1;
    if ((copy = (char *)malloc(len)) == NULL)  return 0;
    memcpy(copy, str, len);

    return copy;
}

// New a JsonObject structure
static JsonObject *cJsonNewItem() {
    JsonObject* node = (JsonObject *)malloc(sizeof(JsonObject));
    if (node)
        memset(node, 0, sizeof(JsonObject));

    return node;
}

// Delete a JsonObject structure
void cJsonDelete(JsonObject *object) {
    JsonObject *next;

    while (object) {
        next = object->next;

        if (!(object->type & JSON_REFERENCE) && object->child )
            cJsonDelete(object->child);

        if (!(object->type & JSON_REFERENCE) && object->valueString )
            free(object->valueString);

        if ( object->string )
            free(object->string);

        free(object);
        object = next;
    }
}

// Render the cstring provided to an escaped version that can be printed.
static char *print_string_ptr(const char *str) {
    const char *ptr;
    char *ptr_out, *out_string;
    int len = 0;
    unsigned char token;

    if (!str)
        return cJsonStrDup("");
    ptr = str;
    while ((token = *ptr) && ++len) {
        if (strchr("\"\\\b\f\n\r\t", token))
            ++len;
        else if (token < 32)
            len += 5;
        ++ptr;
    }

    if (!(out_string = (char*)malloc(len + 3)))
        return NULL;

    ptr_out = out_string;
    ptr = str;
    *ptr_out++ = '\"';
    while (*ptr) {
        if ((unsigned char) *ptr > 31 && *ptr != '\"' && *ptr != '\\')
            *ptr_out++ = *ptr++;
        else {
            *ptr_out++ = '\\';
            switch (token = *ptr++) {
                case '\\': *ptr_out++ = '\\'; break;
                case '\"': *ptr_out++ = '\"'; break;
                case '\b': *ptr_out++ = 'b'; break;
                case '\f': *ptr_out++ = 'f'; break;
                case '\n': *ptr_out++ = 'n'; break;
                case '\r': *ptr_out++ = 'r'; break;
                case '\t': *ptr_out++ = 't'; break;
                default:
                    // Escape and print.
                    sprintf( ptr_out, "u%04x", token );
                    ptr_out += 5;
                    break;
            }
        }
    }
    *ptr_out++ = '\"';
    *ptr_out++ = 0;
    return out_string;
}

// Utility to jump whitespace and cr/lf.
static const char *skip(const char *in) {
    while (in && *in && (unsigned char)*in <= 32)
        in++;

    return in;
}

// Predeclare these prototypes.
static const char *parse_value(JsonObject *item, const char *value);
static char *print_value(const JsonObject *item, int depth, int fmt);

static const char *parse_number(JsonObject *item, const char *num);
static char *print_number(const JsonObject *item);

static const char *parse_string(JsonObject *item, const char *str);
static char *print_string(const JsonObject *item);

static const char *parse_array(JsonObject *item, const char *value);
static char *print_array(const JsonObject *item, int depth, int fmt);

static const char *parse_object(JsonObject *item, const char *value);
static char *print_object(const JsonObject *item, int depth, int fmt);

// Parse an object - create a new root, and populate.
JsonObject* cJsonParse( const char *value ) {
    JsonObject *object;
    global_ep = 0;
    if ((object = cJsonNewItem()) == NULL)
        return NULL;

    if (!parse_value(object, skip(value))) {
        cJsonDelete(object);
        return NULL;
    }

    return object;
}

// Render a cJSON item/entity/structure to text.
char *cJsonPrint(const JsonObject *item) {
    return print_value(item, 0, 1);
}

char *cJsonPrintUnformatted(const JsonObject *item) {
    return print_value(item, 0, 0);
}

// Parser core - when encountering text, process appropriately.
static const char *parse_value(JsonObject *item, const char *value) {
    // Fail on null
    if (!value)
        return 0;

    if (!strncmp(value, "null", 4)) {
        item->type = JSON_NULL;
        return value + 4;
    }

    if (!strncmp(value, "false", 5)) {
        item->type = JSON_FALSE;
        return value + 5;
    }

    if (!strncmp(value, "true", 4)) {
        item->type = JSON_TRUE;
        item->valueInt = 1;
        return value + 4;
    }

    if (*value == '\"')
        return parse_string(item, value);

    if (*value == '-' || (*value >= '0' && *value <= '9'))
        return parse_number(item, value);

    if (*value == '[')
        return parse_array(item, value);

    if (*value == '{')
        return parse_object(item, value);

    // Fail.
    global_ep = value;

    return NULL;
}

// Render a value to text.
static char *print_value(const JsonObject *item, int depth, int fmt) {
    char *out = NULL;

    if (!item)
        return NULL;

    switch ((item->type ) & 255) {
        case JSON_NULL:
            out = cJsonStrDup("null");
            break;
        case JSON_FALSE:
            out = cJsonStrDup("false");
            break;
        case JSON_TRUE:
            out = cJsonStrDup("true");
            break;
        case JSON_NUMBER:
            out = print_number(item);
            break;
        case JSON_STRING:
            out = print_string(item);
            break;
        case JSON_ARRAY:
            out = print_array(item, depth, fmt);
            break;
        case JSON_OBJECT:
            out = print_object(item, depth, fmt);
            break;
    }

    return out;
}


// Parse the input text to generate a number, and populate the result into item.
static const char *parse_number(JsonObject *item, const char *num) {
    double n = 0;
    double sign = 1;
    double scale = 0;
    int subscale = 0;
    int signsubscale = 1;

    // Has sign
    if (*num == '-') {
        sign = -1;
        num++;
    }
    // is zero
    if (*num == '0') {
        num++;
    }
    // Number
    if ((*num >= '1') && (*num <= '9')) {
        do {
            n = (n * 10.0) + (*num++ - '0');
        }
        while ((*num >= '0') && (*num<='9'));
    }
    // Fractional part
    if ((*num == '.') && (num[1] >= '0') && (num[1] <= '9')) {
        num++;
        do {
            n = (n  *10.0) + (*num++ - '0');
            scale--;
        } while ((*num >= '0') && (*num <= '9'));
    }

    // Exponent
    if ((*num == 'e') || (*num == 'E')) {
        num++;
        // With sign
        if (*num == '+') {
            num++;
        } else if (*num == '-') {
            signsubscale = -1;
            num++;
        }
        // Number
        while ((*num>='0') && (*num<='9')) {
            subscale = (subscale * 10) + (*num++ - '0');
        }
    }

    // number = +/- number.fraction * 10^+/- exponent
    n = sign * n * pow(10.0, (scale + subscale * signsubscale));

    item->valueDouble = n;
    item->valueInt = (int)n;
    item->type = JSON_NUMBER;

    return num;
}

// Render the number nicely from the given item into a string.
static char *print_number(const JsonObject *item) {
    char *str;
    double f, f2;
    int64_t i;

    str = (char*)malloc(64);
    if (str) {
        f = item->valueDouble;
        i = f;
        f2 = i;
        if ( f2 == f && item->valueInt >= LLONG_MIN && item->valueInt <= LLONG_MAX )
            sprintf(str, "%lld", (long long)item->valueInt);
        else
            sprintf(str, "%g", item->valueDouble);
    }

    return str;
}

// Parse the input text into an unescaped cstring, and populate item.
static const unsigned char firstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

static const char *parse_string(JsonObject *item, const char *str) {
    const char *ptr = str + 1;
    char *out_string;
    int len = 0;
    unsigned uc, uc2;  // unicode
    char *ptr_out;

    // Not a string
    if (*str != '\"') {
        global_ep = str;
        return NULL;
    }

    // Skip escaped quotes.
    while (*ptr != '\"' && *ptr && ++len) {
        if (*ptr++ == '\\')
            ptr++;
    }

    if ((out_string = (char*)malloc(len + 1)) == NULL)
        return NULL;

    ptr = str + 1;
    ptr_out = out_string;
    while (*ptr != '\"' && *ptr) {
        if (*ptr != '\\')
            *ptr_out++ = *ptr++;
        else {
            ptr++;
            switch (*ptr) {
                case 'b':
                    *ptr_out++ ='\b';
                    break;
                case 'f':
                    *ptr_out++ ='\f';
                    break;
                case 'n':
                    *ptr_out++ ='\n';
                    break;
                case 'r':
                    *ptr_out++ ='\r';
                    break;
                case 't':
                    *ptr_out++ ='\t';
                    break;
                case 'u':
                    // Transcode utf16 to utf8.
                    // Get the unicode char.
                    sscanf(ptr + 1,"%4x", &uc);
                    ptr += 4;

                    // Check for invalid.
                    if ((uc >= 0xDC00 && uc <= 0xDFFF) || uc == 0)
                        break;

                    // UTF16 surrogate pairs.
                    if (uc >= 0xD800 && uc <= 0xDBFF) {
                        if (ptr[1] != '\\' || ptr[2] != 'u')
                            // Missing second-half of surrogate.
                            break;
                        sscanf(ptr + 3, "%4x", &uc2);
                        ptr += 6;
                        if (uc2 < 0xDC00 || uc2 > 0xDFFF)
                            // Invalid second-half of surrogate.
                            break;
                        uc = 0x10000 | ( ( uc & 0x3FF ) << 10 ) | ( uc2 & 0x3FF );
                    }

                    len = 4;
                    if (uc < 0x80)
                        len = 1;
                    else if (uc < 0x800)
                        len = 2;
                    else if (uc < 0x10000)
                        len = 3;
                    ptr_out += len;

                    switch (len) {
                        case 4:
                            *--ptr_out = ((uc | 0x80) & 0xBF );
                            uc >>= 6;
                        case 3:
                            *--ptr_out = (( uc | 0x80) & 0xBF );
                            uc >>= 6;
                        case 2:
                            *--ptr_out = (( uc | 0x80) & 0xBF );
                            uc >>= 6;
                        case 1:
                            *--ptr_out = (uc | firstByteMark[len]);
                    }
                    ptr_out += len;
                    break;
                default:
                    *ptr_out++ = *ptr;
                    break;
            }
            ++ptr;
        }
    }
    *ptr_out = '\0';
    if (*ptr == '\"')
        ++ptr;

    item->valueString = out_string;
    item->type = JSON_STRING;

    return ptr;
}

// Invote print_string_ptr (which is useful) on an item.
static char *print_string(const JsonObject *item) {
    return print_string_ptr(item->valueString);
}

// Build an array from input text.
static const char *parse_array(JsonObject *item, const char *value) {
    JsonObject *child;

    if (*value != '[') {
        // Not an array!
        global_ep = value;
        return 0;
    }

    item->type = JSON_ARRAY;
    value = skip(value + 1);

    // empty array
    if (*value == ']')
        return value + 1;

    if (!(item->child = child = cJsonNewItem()))
        return NULL;

    if (!(value = skip(parse_value(child, skip(value)))))
        return NULL;

    while (*value == ',') {
        JsonObject *new_item;
        if (!(new_item = cJsonNewItem()))
            return NULL;

        child->next = new_item;
        new_item->prev = child;
        child = new_item;

        if (!(value = skip(parse_value(child, skip(value + 1)))))
            return NULL;
    }

    if ( *value == ']' )
        return value + 1;

    /* Malformed. */
    global_ep = value;
    return NULL;
}


// Render an array to text
static char *print_array(const JsonObject *item, int depth, int fmt) {
    char **entries;
    char *out = 0, *ptr, *ret;
    int len = 5;
    JsonObject *child = item->child;
    int numentries = 0, i = 0, fail = 0;

    // How many entries in the array?
    while (child) {
        ++numentries;
        child = child->next;
    }

    // Allocate an array to hold the values for each.
    if (!(entries = (char**)malloc( numentries * sizeof(char*))))
        return NULL;
    memset( entries, 0, numentries * sizeof(char*) );

    // Retrieve all the results.
    child = item->child;
    while (child && !fail) {
        ret = print_value(child, depth + 1, fmt);
        entries[i++] = ret;
        if (ret)
            len += strlen(ret) + 2 + (fmt ? 1 : 0);
        else
            fail = 1;
        child = child -> next;
    }

    // If we didn't fail, try to malloc the output string.
    if (!fail) {
        out = (char*)malloc(len);
        if (!out)
            fail = 1;
    }

    // Handle failure.
    if (fail) {
        for (i = 0; i < numentries; ++i)
            if (entries[i])
                free(entries[i]);
        free(entries);
        return NULL;
    }

    // Compose the output array.
    *out = '[';
    ptr = out + 1;
    *ptr = 0;
    for (i = 0; i < numentries; ++i) {
        strcpy(ptr, entries[i]);
        ptr += strlen(entries[i]);
        if (i != numentries - 1) {
            *ptr++ = ',';
            if (fmt)
                *ptr++ = ' ';
            *ptr = 0;
        }
        free(entries[i]);
    }
    free( entries );
    *ptr++ = ']';
    *ptr++ = 0;
    return out;
}

// Build an object from the text.
static const char *parse_object(JsonObject *item, const char *value) {
    JsonObject *child;

    // Not an object
    if (*value != '{') {
        global_ep = value;
        return NULL;
    }

    item->type = JSON_OBJECT;
    value = skip(value + 1);

    // Empty object
    if (*value == '}')
        return value + 1;

    if (!(item->child = child = cJsonNewItem()))
        return NULL;

    if (!(value = skip(parse_string(child, skip(value)))))
        return NULL;

    child->string = child->valueString;
    child->valueString = 0;
    if (*value != ':') {
        global_ep = value;
        return NULL;
    }
    if (!(value = skip( parse_value(child, skip(value + 1)))))
        return NULL;

    while (*value == ',') {
        JsonObject *new_item;
        if (!(new_item = cJsonNewItem()))
            return NULL;

        child->next = new_item;
        new_item->prev = child;
        child = new_item;
        if (!(value = skip(parse_string(child, skip(value + 1)))))
            return NULL;

        child->string = child->valueString;
        child->valueString = 0;
        if (*value != ':') {
            global_ep = value;
            return NULL;
        }
        if (!(value = skip(parse_value(child, skip( value + 1 )))))
            return NULL;
    }

    if (*value == '}')
        return value + 1;

    /* Malformed. */
    global_ep = value;
    return NULL;
}


// Render an object to text.
static char *print_object(const JsonObject *item, int depth, int fmt) {
    char **entries = 0, **names = 0;
    char *out = 0, *ptr, *ret, *str;
    int len = 7, i = 0, j;
    JsonObject *child = item->child;
    int numentries = 0, fail = 0;

    // Count the number of entries.
    while (child) {
        ++numentries;
        child = child->next;
    }
    // Allocate space for the names and the objects.
    if (!(entries = (char**)malloc(numentries * sizeof(char*))))
        return NULL;

    if (!(names = (char**)malloc(numentries * sizeof(char*)))) {
        free(entries);
        return NULL;
    }
    memset(entries, 0, sizeof(char*) * numentries);
    memset(names, 0, sizeof(char*) * numentries);

    // Collect all the results into our arrays.
    child = item->child;
    ++depth;
    if (fmt)
        len += depth;
    while (child) {
        names[i] = str = print_string_ptr(child->string);
        entries[i++] = ret = print_value(child, depth, fmt);
        if (str && ret)
            len += strlen(ret) + strlen(str) + 2 + (fmt ? 2 + depth : 0);
        else
            fail = 1;
        child = child->next;
    }

    // Try to allocate the output string.
    if (!fail) {
        out = (char*)malloc(len);
        if (!out)
            fail = 1;
    }

    // Handle failure.
    if (fail) {
        for (i = 0; i < numentries; ++i) {
            if (names[i])
                free(names[i]);
            if (entries[i])
                free(entries[i]);
        }
        free(names);
        free(entries);
        return 0;
    }

    // Compose the output.
    *out = '{';
    ptr = out + 1;
    if (fmt)
        *ptr++ = '\n';
    *ptr = 0;
    for (i = 0; i < numentries; ++i) {
        if (fmt)
            for (j = 0; j < depth; ++j)
                *ptr++ = '\t';
        strcpy(ptr, names[i]);
        ptr += strlen(names[i]);
        *ptr++ = ':';
        if (fmt)
            *ptr++ = '\t';
        strcpy(ptr, entries[i]);
        ptr += strlen(entries[i]);
        if (i != numentries - 1)
            *ptr++ = ',';
        if (fmt)
            *ptr++ = '\n';
        *ptr = 0;
        free(names[i]);
        free(entries[i]);
    }

    free(names);
    free(entries);
    if (fmt) {
        for (i = 0; i < depth - 1; ++i)
            *ptr++ = '\t';
    }

    *ptr++ = '}';
    *ptr++ = 0;

    return out;
}


int cJsonGetArraySize(const JsonObject *array) {
    JsonObject *c = array->child;
    int i = 0;

    while (c) {
        ++i;
        c = c->next;
    }

    return i;
}


JsonObject *cJsonGetArrayItem(const JsonObject *array, int index) {
    JsonObject *c = array->child;

    while ( c && index > 0 ) {
        --index;
        c = c->next;
    }

    return c;
}


JsonObject *cJsonGetObjectItem(const JsonObject *object, const char *string) {
    JsonObject *c = object->child;

    while (c && cJsonStrCaseCmp(c->string, string))
        c = c->next;

    return c;
}

int cJsonHasObjectItem(const JsonObject *object, const char *string) {
    return cJsonGetObjectItem(object, string) ? 1 : 0;
}

// Utility for array list handling.
static void suffix_object(JsonObject *prev, JsonObject *item) {
    prev->next = item;
    item->prev = prev;
}

// Utility for handling references.
static JsonObject *create_reference(JsonObject *item) {
    JsonObject *ref;
    if (!(ref = cJsonNewItem()))
        return NULL;
    memcpy(ref, item, sizeof(JsonObject));

    ref->string = NULL;
    ref->type |= JSON_REFERENCE;
    ref->next = ref->prev = NULL;
    return ref;
}


// Add item to array/object.
void cJsonAddItemToArray(JsonObject *array, JsonObject *item) {
    JsonObject *c = array->child;
    if (!item)
        return;

    if (!c) {
        array->child = item;
    } else {
        while (c && c->next)
            c = c->next;
        suffix_object(c, item);
    }
}

void cJsonAddItemToObject( JsonObject *object, const char *string, JsonObject *item) {
    if (!item)
        return;

    if (item->string )
        free(item->string);

    item->string = cJsonStrDup(string);
    cJsonAddItemToArray(object, item);
}

void cJsonAddItemReferenceToArray(JsonObject *array, JsonObject *item) {
    cJsonAddItemToArray(array, create_reference(item));
}

void cJsonAddItemReferenceToObject(JsonObject *object, const char *string, JsonObject *item) {
    cJsonAddItemToObject(object, string, create_reference(item));
}

JsonObject *cJsonDetachItemFromArray(JsonObject *array, int which) {
    JsonObject *c = array->child;
    while (c && which > 0) {
        c = c->next;
        --which;
    }

    if (!c)
        return 0;

    if (c->prev)
        c->prev->next = c->next;

    if (c->next)
        c->next->prev = c->prev;

    if (c == array->child)
        array->child = c->next;

    c->prev = c->next = NULL;
    return c;
}

void cJsonDeleteItemFromArray(JsonObject *array, int which) {
    cJsonDelete(cJsonDetachItemFromArray(array, which));
}

JsonObject *cJsonDetachItemFromObject(JsonObject *object, const char *string) {
    int i = 0;
    JsonObject *c = object->child;
    while (c && cJsonStrCaseCmp(c->string, string)) {
        ++i;
        c = c->next;
    }

    if (c)
        return cJsonDetachItemFromArray(object, i);

    return NULL;
}

void cJsonDeleteItemFromObject(JsonObject *object, const char *string) {
    cJsonDelete(cJsonDetachItemFromObject(object, string));
}

// Replace array/object items with new ones.
void cJsonReplaceItemInArray(JsonObject *array, int which, JsonObject *newitem ) {
    JsonObject *c = array->child;
    while (c && which > 0) {
        c = c->next;
        --which;
    }

    if (!c)  return;

    newitem->next = c->next;
    newitem->prev = c->prev;
    if (newitem->next)
        newitem->next->prev = newitem;

    if (c == array->child)
        array->child = newitem;
    else
        newitem->prev->next = newitem;

    c->next = c->prev = NULL;
    cJsonDelete(c);
}

void cJsonReplaceItemInObject(JsonObject *object, const char *string, JsonObject *newitem) {
    int i = 0;
    JsonObject *c = object->child;
    while (c && cJsonStrCaseCmp(c->string, string)) {
        ++i;
        c = c->next;
    }
    if (c) {
        newitem->string = cJsonStrDup(string);
        cJsonReplaceItemInArray( object, i, newitem );
    }
}

// Create basic types:
JsonObject *cJsonCreateNull() {
    JsonObject *item = cJsonNewItem();
    if (item)
        item->type = JSON_NULL;

    return item;
}

JsonObject *cJsonCreateTrue() {
    JsonObject *item = cJsonNewItem();
    if (item)
        item->type = JSON_TRUE;

    return item;
}

JsonObject *cJsonCreateFalse() {
    JsonObject *item = cJsonNewItem();
    if (item)
        item->type = JSON_FALSE;

    return item;
}

JsonObject *cJsonCreateBool(int b) {
    JsonObject *item = cJsonNewItem();
    if (item)
        item->type = b ? JSON_TRUE : JSON_FALSE;

    return item;
}

JsonObject *cJsonCreateInt(int64_t num) {
    JsonObject *item = cJsonNewItem();
    if (item) {
        item->type = JSON_NUMBER;
        item->valueDouble = num;
        item->valueInt = num;
    }

    return item;
}

JsonObject *cJsonCreateDouble(double num) {
    JsonObject *item = cJsonNewItem();
    if (item) {
        item->type = JSON_NUMBER;
        item->valueDouble = num;
        item->valueInt = num;
    }

    return item;
}

JsonObject *cJsonCreateString(const char *string) {
    JsonObject *item = cJsonNewItem();
    if ( item ) {
        item->type = JSON_STRING;
        item->valueString = cJsonStrDup(string);
    }

    return item;
}

JsonObject *cJsonCreateArray() {
    JsonObject *item = cJsonNewItem();
    if (item)
        item->type = JSON_ARRAY;

    return item;
}

JsonObject *cJsonCreateObject() {
    JsonObject *item = cJsonNewItem();
    if (item)
        item->type = JSON_OBJECT;

    return item;
}


// Create Arrays.
JsonObject *cJsonCreateIntArray(int64_t *numbers, int count) {
    int i;
    JsonObject *n = 0, *p = 0, *a = cJsonCreateArray();
    for (i = 0; a && i < count; ++i) {
        n = cJsonCreateInt(numbers[i]);
        if (!i)
            a->child = n;
        else
            suffix_object(p, n);
        p = n;
    }

    return a;
}

JsonObject *cJsonCreateDoubleArray(double *numbers, int count) {
    int i;
    JsonObject *n = 0, *p = 0, *a = cJsonCreateArray();
    for ( i = 0; a && i < count; ++i ) {
        n = cJsonCreateDouble(numbers[i]);
        if (!i)
            a->child = n;
        else
            suffix_object( p, n );
        p = n;
    }

    return a;
}

JsonObject *cJsonCreateStringArray(const char **strings, int count){
    int i;
    JsonObject *n = 0, *p = 0, *a = cJsonCreateArray();
    for ( i = 0; a && i < count; ++i ) {
        n = cJsonCreateString( strings[i] );
        if ( ! i )
            a->child = n;
        else
            suffix_object( p, n );
        p = n;
    }

    return a;
}
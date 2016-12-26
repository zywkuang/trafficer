/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 10/28/16
**/

#ifndef TRAFFICER_JSON_H
#define TRAFFICER_JSON_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* JsonObject Types: */
#define JSON_FALSE 0
#define JSON_TRUE 1
#define JSON_NULL 2
#define JSON_NUMBER 3
#define JSON_STRING 4
#define JSON_ARRAY 5
#define JSON_OBJECT 6
#define JSON_REFERENCE 256

// JsonObject structure
typedef struct JsonObject {
    // next/prev allow you to walk array/object chains.
    struct JsonObject *next;
    struct JsonObject *prev;

    // an array or object item will have a child pointer pointing to a chain of the items in the array/object.
    struct JsonObject *child;

    int type; // The type of the item as above.

    char *valueString; // if type == JSON_STRING, then the item is string
    int64_t valueInt;  // if type == JSON_NUMBER, then the item is number
    double valueDouble; // if type == JSON_NUMBER, the the item is number

    char *string; // The item's name string, if this item is the child of, or is in the list of subitems of an object.
} JsonObject;

// supply a block of json, and this returns a JsonObject you can interrogate. Call JsonDelete when finished.
extern JsonObject* cJsonParse(const char *value);

// Render a JsonObject entity to text for transfer/storage. Free the char* when finished.
extern char* cJsonPrint(const JsonObject *item);

// Render a JsonObject entity to text for transfer/storage without any formatting. Free the char* when finished.
extern char* cJsonPrintUnformatted(const JsonObject *item);

// Delete a JsonObject entity and all subentities.
extern void cJsonDelete(JsonObject *item);

// Returns the number of items in an array (or object).
extern int cJsonGetArraySize(const JsonObject *item);

// Retrieve item number "item" from array "array". Returns NULL if unsuccessful.
extern JsonObject* cJsonGetArrayItem(const JsonObject *array, int index);

// Get item "string" from object. Case insensitive.
extern JsonObject* cJsonGetObjectItem(const JsonObject *object, const char *string);
extern int cJsonHasObjectItem(const JsonObject *object, const char *string);

// These calls create a JsonObject item of the appropriate type.
extern JsonObject* cJsonCreateNull();
extern JsonObject* cJsonCreateTrue();
extern JsonObject* cJsonCreateFalse();
extern JsonObject* cJsonCreateBool(int b);
extern JsonObject* cJsonCreateInt(int64_t num);
extern JsonObject* cJsonCreateDouble(double num);
extern JsonObject* cJsonCreateString(const char *string);
extern JsonObject* cJsonCreateArray();
extern JsonObject* cJsonCreateObject();

// These utilities create an Array of count items.
extern JsonObject* cJsonCreateIntArray(const int64_t *numbers, int count);
extern JsonObject* cJsonCreateDoubleArray(const double *numbers, int count);
extern JsonObject* cJsonCreateStringArray(const char **strings, int count);

// Append item to the specified array/object.
extern void cJsonAddItemToArray(JsonObject *array, JsonObject *item);
extern void cJsonAddItemToObject(JsonObject *object, const char *string, JsonObject *item);

// Append reference to item to the specified array/object.
// Use this when you want to add an existing JsonObject to a new JsonObject, but don't want to corrupt your existing JsonObject.
extern void cJsonAddItemReferenceToArray(JsonObject *array, JsonObject *item);
extern void cJsonAddItemReferenceToObject(JsonObject *object, const char *string, JsonObject *item);

/// Remove/Detatch items from Arrays/Objects.
extern JsonObject* cJsonDetachItemFromArray(JsonObject *array, int which);
extern void cJsonDeleteItemFromArray(JsonObject *array, int which);
extern JsonObject* cJsonDetachItemFromObject(JsonObject *object, const char *string);
extern void cJsonDeleteItemFromObject(JsonObject *object, const char *string);

// Update array items.
extern void cJsonReplaceItemInArray(JsonObject *array, int which, JsonObject *newitem);
extern void cJsonReplaceItemInObject(JsonObject *object, const char *string, JsonObject *newitem);

extern const char* cJsonGetErrorPtr();

#define cJsonAddNullToObject(object, name)          cJsonAddItemToObject(object, name, cJsonCreateNull())
#define cJsonAddTrueToObject(object, name)          cJsonAddItemToObject(object, name, cJsonCreateTrue())
#define cJsonAddFalseToObject(object, name)         cJsonAddItemToObject(object, name, cJsonCreateFalse())
#define cJsonAddIntToObject(object, name, n)        cJsonAddItemToObject(object, name, cJsonCreateInt(n))
#define cJsonAddDoubleToObject(object, name, n)     cJsonAddItemToObject(object, name, cJsonCreateDouble(n))
#define cJsonAddStringToObject(object, name, s)     cJsonAddItemToObject(object, name, cJsonCreateString(s))

#ifdef __cplusplus
}
#endif


#endif //TRAFFICER_JSON_H


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "allowed_nssai.h"

OpenAPI_allowed_nssai_t *OpenAPI_allowed_nssai_create(
    OpenAPI_list_t *allowed_snssai_list,
    OpenAPI_access_type_e access_type
)
{
    OpenAPI_allowed_nssai_t *allowed_nssai_local_var = ogs_malloc(sizeof(OpenAPI_allowed_nssai_t));
    ogs_assert(allowed_nssai_local_var);

    allowed_nssai_local_var->allowed_snssai_list = allowed_snssai_list;
    allowed_nssai_local_var->access_type = access_type;

    return allowed_nssai_local_var;
}

void OpenAPI_allowed_nssai_free(OpenAPI_allowed_nssai_t *allowed_nssai)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == allowed_nssai) {
        return;
    }
    if (allowed_nssai->allowed_snssai_list) {
        OpenAPI_list_for_each(allowed_nssai->allowed_snssai_list, node) {
            OpenAPI_allowed_snssai_free(node->data);
        }
        OpenAPI_list_free(allowed_nssai->allowed_snssai_list);
        allowed_nssai->allowed_snssai_list = NULL;
    }
    ogs_free(allowed_nssai);
}

cJSON *OpenAPI_allowed_nssai_convertToJSON(OpenAPI_allowed_nssai_t *allowed_nssai)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (allowed_nssai == NULL) {
        ogs_error("OpenAPI_allowed_nssai_convertToJSON() failed [AllowedNssai]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (!allowed_nssai->allowed_snssai_list) {
        ogs_error("OpenAPI_allowed_nssai_convertToJSON() failed [allowed_snssai_list]");
        return NULL;
    }
    cJSON *allowed_snssai_listList = cJSON_AddArrayToObject(item, "allowedSnssaiList");
    if (allowed_snssai_listList == NULL) {
        ogs_error("OpenAPI_allowed_nssai_convertToJSON() failed [allowed_snssai_list]");
        goto end;
    }
    OpenAPI_list_for_each(allowed_nssai->allowed_snssai_list, node) {
        cJSON *itemLocal = OpenAPI_allowed_snssai_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI_allowed_nssai_convertToJSON() failed [allowed_snssai_list]");
            goto end;
        }
        cJSON_AddItemToArray(allowed_snssai_listList, itemLocal);
    }

    if (allowed_nssai->access_type == OpenAPI_access_type_NULL) {
        ogs_error("OpenAPI_allowed_nssai_convertToJSON() failed [access_type]");
        return NULL;
    }
    if (cJSON_AddStringToObject(item, "accessType", OpenAPI_access_type_ToString(allowed_nssai->access_type)) == NULL) {
        ogs_error("OpenAPI_allowed_nssai_convertToJSON() failed [access_type]");
        goto end;
    }

end:
    return item;
}

OpenAPI_allowed_nssai_t *OpenAPI_allowed_nssai_parseFromJSON(cJSON *allowed_nssaiJSON)
{
    OpenAPI_allowed_nssai_t *allowed_nssai_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *allowed_snssai_list = NULL;
    OpenAPI_list_t *allowed_snssai_listList = NULL;
    cJSON *access_type = NULL;
    OpenAPI_access_type_e access_typeVariable = 0;
    allowed_snssai_list = cJSON_GetObjectItemCaseSensitive(allowed_nssaiJSON, "allowedSnssaiList");
    if (!allowed_snssai_list) {
        ogs_error("OpenAPI_allowed_nssai_parseFromJSON() failed [allowed_snssai_list]");
        goto end;
    }
        cJSON *allowed_snssai_list_local = NULL;
        if (!cJSON_IsArray(allowed_snssai_list)) {
            ogs_error("OpenAPI_allowed_nssai_parseFromJSON() failed [allowed_snssai_list]");
            goto end;
        }

        allowed_snssai_listList = OpenAPI_list_create();

        cJSON_ArrayForEach(allowed_snssai_list_local, allowed_snssai_list) {
            if (!cJSON_IsObject(allowed_snssai_list_local)) {
                ogs_error("OpenAPI_allowed_nssai_parseFromJSON() failed [allowed_snssai_list]");
                goto end;
            }
            OpenAPI_allowed_snssai_t *allowed_snssai_listItem = OpenAPI_allowed_snssai_parseFromJSON(allowed_snssai_list_local);
            if (!allowed_snssai_listItem) {
                ogs_error("No allowed_snssai_listItem");
                goto end;
            }
            OpenAPI_list_add(allowed_snssai_listList, allowed_snssai_listItem);
        }

    access_type = cJSON_GetObjectItemCaseSensitive(allowed_nssaiJSON, "accessType");
    if (!access_type) {
        ogs_error("OpenAPI_allowed_nssai_parseFromJSON() failed [access_type]");
        goto end;
    }
    if (!cJSON_IsString(access_type)) {
        ogs_error("OpenAPI_allowed_nssai_parseFromJSON() failed [access_type]");
        goto end;
    }
    access_typeVariable = OpenAPI_access_type_FromString(access_type->valuestring);

    allowed_nssai_local_var = OpenAPI_allowed_nssai_create (
        allowed_snssai_listList,
        access_typeVariable
    );

    return allowed_nssai_local_var;
end:
    if (allowed_snssai_listList) {
        OpenAPI_list_for_each(allowed_snssai_listList, node) {
            OpenAPI_allowed_snssai_free(node->data);
        }
        OpenAPI_list_free(allowed_snssai_listList);
        allowed_snssai_listList = NULL;
    }
    return NULL;
}

OpenAPI_allowed_nssai_t *OpenAPI_allowed_nssai_copy(OpenAPI_allowed_nssai_t *dst, OpenAPI_allowed_nssai_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_allowed_nssai_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_allowed_nssai_convertToJSON() failed");
        return NULL;
    }

    content = cJSON_Print(item);
    cJSON_Delete(item);

    if (!content) {
        ogs_error("cJSON_Print() failed");
        return NULL;
    }

    item = cJSON_Parse(content);
    ogs_free(content);
    if (!item) {
        ogs_error("cJSON_Parse() failed");
        return NULL;
    }

    OpenAPI_allowed_nssai_free(dst);
    dst = OpenAPI_allowed_nssai_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}


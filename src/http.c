#include "dwelui/string.h"
#include <dwelui/http.h>
#include <stddef.h>
#include <stdlib.h>

struct HttpRequest {
    const String *raw;
};

HttpRequest *http_request_from_string(String s) {
    const String rawString = string_clone(s);

    HttpRequest *req = malloc(sizeof(HttpRequest));
    if (!req) {
        return nullptr;
    }

    req->raw = &rawString;

    return req;
}

#ifndef DWELUI_HTTP_H
#define DWELUI_HTTP_H

#include <dwelui/string.h>

typedef struct HttpRequest HttpRequest;

typedef enum {
    HTTP_PROTOCOL_1_1,
} HttpProtocol;

typedef enum {
    HTTP_METHOD_GET,
    HTTP_METHOD_HEAD,
    HTTP_METHOD_POST,
    HTTP_METHOD_PUT,
    HTTP_METHOD_DELETE,
    HTTP_METHOD_CONNECT,
    HTTP_METHOD_OPTIONS,
    HTTP_METHOD_TRACE,
    HTTP_METHOD_PATCH,
} HttpMethod;

HttpRequest   *http_request_from_string(String s);
HttpProtocol   http_request_protocol(const HttpRequest *req);
HttpMethod     http_request_method(const HttpRequest *req);

StringView     http_request_url(const HttpRequest *req);
StringView     http_request_path(const HttpRequest *req);
StringView     http_request_query(const HttpRequest *req);
StringViewList http_request_query_keys(const HttpRequest *req);
bool           http_request_query_key_exists(const HttpRequest *req, const char *key);
StringView     http_request_query_value(const HttpRequest *req, const char *key);
StringView     http_request_fragment(const HttpRequest *req);

StringViewList http_request_header_keys(const HttpRequest *req);
bool           http_request_header_key_exists(const HttpRequest *req, const char *key);
StringView     http_request_header_value(const HttpRequest *req, const char *key);

#endif // DWELUI_HTTP_H

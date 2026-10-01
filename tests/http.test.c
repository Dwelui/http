#include <dwelui/test.h>
#include <dwelui/http.h>
#include <dwelui/string.h>
#include <stdio.h>

typedef struct {
    const char *fixture;
    const char *expected;
} PathData;
TEST_DATA_PROVIDER(pathDataProvider, {
    static const PathData data1 = {"tests/fixtures/http_1_1/request/get/index.http", "/"};
    test_data_add("/", data1);

    static const PathData data2 = {"tests/fixtures/http_1_1/request/get/path.http",
                                   "/a/very/long/request/path/index.html"};
    test_data_add("/a/very/long/request/path/index.html", data2);

    static const PathData data3 = {"tests/fixtures/http_1_1/request/get/query.http", "/"};
    test_data_add("/", data3);
})

String fixture_to_string(const char *path) {
    FILE *fixtureFd = fopen(path, "r");
    if (nullptr == fixtureFd) {
        perror("fopen");
    }

    StringBuffer buffer = string_buffer_start();

    const size_t chuckSize = 1024;
    char         data[chuckSize + 1];
    size_t       length = 0;

    do {
        length = fread(data, 1, chuckSize, fixtureFd);

        string_buffer_append_data(&buffer, data, length);
    } while (0 != length);

    String string = string_from_buffer(buffer);
    string_buffer_destroy(&buffer);

    // fixes line endings into http end of lines
    StringView search  = string_view_from_cstr("\n");
    StringView replace = string_view_from_cstr("\r\n");
    string_replace(&string, search, replace, nullptr);

    return string;
}

TEST(request_path, {
    const PathData  *data     = test_data_get(PathData);
    const String     string   = fixture_to_string(data->fixture);
    const StringView expected = string_view_from_cstr(data->expected);

    HttpRequest     *req = http_request_from_string(string);
    string_destroy((String *)&string);

    const StringView reqPath = http_request_path(req);

    test_assert(string_view_equal(reqPath, expected));
})
TEST_OPTIONS(request_path, .dataProvider = pathDataProvider())

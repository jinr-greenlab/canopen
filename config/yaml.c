#include <string.h>
#include <yaml.h>

char * human_readable_event_types[] = {
    "YAML_NO_EVENT",
    "YAML_STREAM_START_EVENT",
    "YAML_STREAM_END_EVENT",
    "YAML_DOCUMENT_START_EVENT",
    "YAML_DOCUMENT_END_EVENT",
    "YAML_ALIAS_EVENT",
    "YAML_SCALAR_EVENT",
    "YAML_SEQUENCE_START_EVENT",
    "YAML_SEQUENCE_END_EVENT",
    "YAML_MAPPING_START_EVENT",
    "YAML_MAPPING_END_EVENT"
};

enum state {
    NO,
    FOO,
    BAR
};

static void consume_foo(yaml_event_t * e) {
    printf("consume_foo: foo: %s\n", (char *)e->data.scalar.value);
}

static void consume_bar_item(yaml_event_t * e) {
    printf("consume_bar_item: item: %s\n", (char *)e->data.scalar.value);
}

int main(int argc, char** argv)
{
    yaml_parser_t parser;
    yaml_event_t event;
    yaml_event_t value_event;

    int done = 0;
    enum state state = NO;

    yaml_parser_initialize(&parser);

    FILE *input = fopen("file.yaml", "rb");

    yaml_parser_set_input_file(&parser, input);

    while (!done) {
        if (!yaml_parser_parse(&parser, &event))
            return 1;

        // printf("%s\n", human_readable_event_types[event.type]);

        if (event.type == YAML_SCALAR_EVENT) {
            if (state == NO) {
                if (strcmp((char *)event.data.scalar.value, "foo") == 0) {
                    state = FOO;
                }
                else if (strcmp((char *)event.data.scalar.value, "bar") == 0) {
                    state = BAR;
                }
            }
            else if (state == FOO) {
                consume_foo(&event);
                state = NO;
            }
            else if (state == BAR) {
                consume_bar_item(&event);
            }
        }
        else if (event.type == YAML_SEQUENCE_END_EVENT) {
            state = NO;
        }

        done = (event.type == YAML_STREAM_END_EVENT);
        yaml_event_delete(&event);
    }

    return 0;
}
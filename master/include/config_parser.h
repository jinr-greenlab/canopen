#include <yaml.h>

enum state;
enum state_node;

long consume_node_id(yaml_event_t * e);
static void consume_can_network(yaml_event_t *e);
static void consume_bitrate_index(yaml_event_t * e);
static void consume_device_type(yaml_event_t * e, long node);
static void consume_vendor_id(yaml_event_t * e, long node);
static void consume_product_code(yaml_event_t * e, long node);
static void consume_revision(yaml_event_t * e, long node);
int config_parser(void);

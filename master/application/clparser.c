#include <cargs.h>
#include <stdbool.h>
#include <stdlib.h>

static struct cag_option options[] = {
  {.identifier = 'c',
    .access_letters = NULL,
    .access_name = "config-file",
    .value_name = "path/to/config.yaml",
    .description = "Path to coniguration file"},

  {.identifier = 'h',
    .access_letters = "h",
    .access_name = "help",
    .description = "Shows the command help"}
};

struct configuration
{
  const char *path;
};

char *clparser(int argc, char** argv)
{
  char identifier;
  const char *value;
  cag_option_context context;
  struct configuration config = {NULL};

  cag_option_prepare(&context, options, CAG_ARRAY_SIZE(options), argc, argv);
  while (cag_option_fetch(&context))
  {
    identifier = cag_option_get(&context);
    switch (identifier)
    {
    case 'c':
      value = cag_option_get_value(&context);
      config.path = value;
      break;
    case 'h':
      printf("Usage: cargsdemo [OPTION]...\n");
      printf("Demonstrates the cargs library.\n\n");
      cag_option_print(options, CAG_ARRAY_SIZE(options), stdout);
      printf("\nNote that all formatting is done by cargs.\n");
      return EXIT_SUCCESS;
    }
  }
  return config.path;
}

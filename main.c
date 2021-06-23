#include "philo.h"

int     main(int argc, char **argv)
{
    t_p  p;

    if (!(parse_args(argc, argv, &p)))
        printf("Invalid Arguments\n");
}
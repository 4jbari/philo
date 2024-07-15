#include "philo.h"


long ft_atoi(char *s)
{
    int n;
    int i;

    i = 0;
    n = 0;
    while (s && (s[i] == '-' || s[i] == '+'))
        if (s[i++] == '-')
            return (printf("NEGATIVE NUMBERS"));
    while (s && *s)
    {
        n *= 10;
        n += (*s - 48);
        s++;
    }
    printf("%d\n", n);
    return (n);
}
void parsing(char **av, data_t *data)
{
    data->num_of_philos = ft_atoi(av[1]);
}
int main(int ac, char **av)
{
    // if (ac != 4 || ac != 5)
    //     return (printf("WRONG ARGUMENTS"));
    data_t data;
    parsing(av, &data);
    printf("%ld\n", data.num_of_philos);

}
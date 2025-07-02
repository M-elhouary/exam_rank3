#include <unistd.h>
#include <stdarg.h>
#include <stddef.h>

int ft_putchar(char c)
{
    return (write(1, &c, 1));
}

int ft_putnbr(int nb)
{
    int count = 0;

    if (nb == -2147483648)
    {
        count += ft_putchar('-');
        count += ft_putchar('2');
        count += ft_putnbr(147483648);
    }
    else if (nb < 0)
    {
        count += ft_putchar('-');
        count += ft_putnbr(-nb);
    }
    else if (nb >= 10)
    {
        count += ft_putnbr(nb / 10);
        count += ft_putnbr(nb % 10);
    }
    else
        count += ft_putchar(nb + '0');
    return (count);
}

int ft_putstr(char *s)
{
    int i = 0;

    if (!s)
        return (write(1, "(null)", 6));
    while (s[i])
        i += write(1, &s[i], 1);
    return (i);
}

int ft_puthex(unsigned int n)
{
    int count = 0;
    char *base = "0123456789abcdef";

    if (n < 16)
        count += ft_putchar(base[n]);
    else
    {
        count += ft_puthex(n / 16);
        count += ft_puthex(n % 16);
    }
    return (count);
}

int ft_printf(const char *str, ...)
{
    va_list args;
    int i = 0;
    int count = 0;

    va_start(args, str);
    while (str[i])
    {
        if (str[i] == '%' && str[i + 1])
        {
            i++;
            if (str[i] == 'd')
                count += ft_putnbr(va_arg(args, int));
            else if (str[i] == 'x')
                count += ft_puthex(va_arg(args, unsigned int));
            else if (str[i] == 's')
                count += ft_putstr(va_arg(args, char *));
            else if (str[i] == '%')
                count += ft_putchar('%');
            else
                count += write(1, &str[i], 1);
        }
        else
            count += write(1, &str[i], 1);
        i++;
    }
    va_end(args);
    return (count);
}

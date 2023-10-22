#include "my_custom_printf.h" // Include your custom header file

/************************* PRINT A CHARACTER *************************/
/**
 * my_printf_char - Custom implementation of printing a character
 * @args: List of arguments
 * @output_buffer: Buffer array to handle output
 * @format_flags: Calculates active format flags
 * @field_width: Field width
 * @precision: Precision specification
 * @length_modifier: Size specifier
 * Return: Number of characters printed
 */
int my_printf_char(va_list args, char output_buffer[],
                  int format_flags, int field_width, int precision, int length_modifier)
{
    char character = va_arg(args, int);

    return (custom_handle_char(character, output_buffer, format_flags, field_width, precision, length_modifier));
}

/************************* PRINT A STRING *************************/
/**
 * my_printf_string - Custom implementation of printing a string
 * @args: List of arguments
 * @output_buffer: Buffer array to handle output
 * @format_flags: Calculates active format flags
 * @field_width: Get field width.
 * @precision: Precision specification
 * @length_modifier: Size specifier
 * Return: Number of characters printed
 */
int my_printf_string(va_list args, char output_buffer[],
                    int format_flags, int field_width, int precision, int length_modifier)
{
    int string_length = 0;
    int i;
    char *str = va_arg(args, char *);

    UNUSED(output_buffer);
    UNUSED(format_flags);
    UNUSED(field_width);
    UNUSED(precision);
    UNUSED(length_modifier);

    if (str == NULL)
    {
        str = "(null)";
        if (precision >= 6)
            str = "      ";
    }

    while (str[string_length] != '\0')
        string_length++;

    if (precision >= 0 && precision < string_length)
        string_length = precision;

    if (field_width > string_length)
    {
        if (format_flags & F_MINUS)
        {
            write(1, &str[0], string_length);
            for (i = field_width - string_length; i > 0; i--)
                write(1, " ", 1);
            return field_width;
        }
        else
        {
            for (i = field_width - string_length; i > 0; i--)
                write(1, " ", 1);
            write(1, &str[0], string_length);
            return field_width;
        }
    }

    return write(1, str, string_length);
}

/************************* PRINT A PERCENT SIGN *************************/
/**
 * my_printf_percent - Custom implementation of printing a percent sign
 * @args: List of arguments
 * @output_buffer: Buffer array to handle output
 * @format_flags: Calculates active format flags
 * @field_width: Get field width.
 * @precision: Precision specification
 * @length_modifier: Size specifier
 * Return: Number of characters printed
 */
int my_printf_percent(va_list args, char output_buffer[],
                     int format_flags, int field_width, int precision, int length_modifier)
{
    UNUSED(args);
    UNUSED(output_buffer);
    UNUSED(format_flags);
    UNUSED(field_width);
    UNUSED(precision);
    UNUSED(length_modifier);

    return write(1, "%%", 1);
}

/************************* PRINT AN INTEGER *************************/
/**
 * my_printf_int - Custom implementation of printing an integer
 * @args: List of arguments
 * @output_buffer: Buffer array to handle output
 * @format_flags: Calculates active format flags
 * @field_width: Get field width.
 * @precision: Precision specification
 * @length_modifier: Size specifier
 * Return: Number of characters printed
 */
int my_printf_int(va_list args, char output_buffer[],
                  int format_flags, int field_width, int precision, int length_modifier)
{
    int index = BUFFER_SIZE - 2;
    int is_negative = 0;
    long int num = va_arg(args, long int);
    unsigned long int converted_num;

    num = custom_convert_size_number(num, length_modifier);

    if (num == 0)
        output_buffer[index--] = '0';

    output_buffer[BUFFER_SIZE - 1] = '\0';
    converted_num = (unsigned long int)num;

    if (num < 0)
    {
        converted_num = (unsigned long int)(-num);
        is_negative = 1;
    }

    while (converted_num > 0)
    {
        output_buffer[index--] = (converted_num % 10) + '0';
        converted_num /= 10;
    }

    index++;

    return custom_write_number(is_negative, index, output_buffer, format_flags, field_width, precision, length_modifier);
}

/************************* PRINT BINARY *************************/
/**
 * my_printf_binary - Custom implementation of printing a binary number
 * @args: List of arguments
 * @output_buffer: Buffer array to handle output
 * @format_flags: Calculates active format flags
 * @field_width: Get field width.
 * @precision: Precision specification
 * @length_modifier: Size specifier
 * Return: Number of characters printed
 */
int my_printf_binary(va_list args, char output_buffer[],
                     int format_flags, int field_width, int precision, int length_modifier)
{
    unsigned int n, m, i, sum;
    unsigned int binary_digits[32];
    int count;

    UNUSED(output_buffer);
    UNUSED(format_flags);
    UNUSED(field_width);
    UNUSED(precision);
    UNUSED(length_modifier);

    n = va_arg(args, unsigned int);
    m = 2147483648; // 2^31
    binary_digits[0] = n / m;
    for (i = 1; i < 32; i++)
    {
        m /= 2;
        binary_digits[i] = (n / m) % 2;
    }
    for (i = 0, sum = 0, count = 0; i < 32; i++)
    {
        sum += binary_digits[i];
        if (sum || i == 31)
        {
            char binary_char = '0' + binary_digits[i];
            write(1, &binary_char, 1);
            count++;
        }
    }
    return count;
}

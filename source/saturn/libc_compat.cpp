#include "saturn_compat.h"

extern "C" int
printf(const char *format, ...)
{
    (void)format;
    return 0;
}

extern "C" int
fprintf(FILE *stream, const char *format, ...)
{
    (void)stream;
    (void)format;
    return 0;
}

static double
abs_double(double value)
{
    return value < 0.0 ? -value : value;
}

extern "C" double
fabs(double value)
{
    return abs_double(value);
}

static double
wrap_pi(double value)
{
    const double pi = 3.14159265358979323846;
    const double two_pi = 6.28318530717958647692;
    while (value > pi) {
        value -= two_pi;
    }
    while (value < -pi) {
        value += two_pi;
    }
    return value;
}

extern "C" double
sin(double value)
{
    value = wrap_pi(value);
    const double b = 1.27323954473516268615;
    const double c = -0.40528473456935108578;
    const double p = 0.225;
    double y = (b * value) + (c * value * abs_double(value));
    return (p * (y * abs_double(y) - y)) + y;
}

extern "C" double
cos(double value)
{
    return sin(value + 1.57079632679489661923);
}

extern "C" float
sinf(float value)
{
    return (float)sin((double)value);
}

extern "C" float
cosf(float value)
{
    return (float)cos((double)value);
}

extern "C" double
atan2(double y, double x)
{
    const double pi = 3.14159265358979323846;
    const double pi_over_4 = 0.78539816339744830962;
    const double three_pi_over_4 = 2.35619449019234492885;

    if (x == 0.0) {
        if (y > 0.0) {
            return 1.57079632679489661923;
        }
        if (y < 0.0) {
            return -1.57079632679489661923;
        }
        return 0.0;
    }

    const double abs_y = abs_double(y) + 0.0000000001;
    double angle;
    if (x >= 0.0) {
        const double r = (x - abs_y) / (x + abs_y);
        angle = pi_over_4 - (pi_over_4 * r);
    } else {
        const double r = (x + abs_y) / (abs_y - x);
        angle = three_pi_over_4 - (pi_over_4 * r);
    }

    if (y < 0.0) {
        return -angle;
    }
    (void)pi;
    return angle;
}

extern "C" double
sqrt(double value)
{
    if (value <= 0.0) {
        return 0.0;
    }

    double guess = value > 1.0 ? value : 1.0;
    for (int i = 0; i < 16; i++) {
        guess = 0.5 * (guess + (value / guess));
    }
    return guess;
}

extern "C" float
logf(float value)
{
    if (value <= 0.0f) {
        return -3.402823466e+38f;
    }

    int exponent = 0;
    while (value > 1.41421356237f) {
        value *= 0.5f;
        exponent++;
    }
    while (value < 0.70710678118f) {
        value *= 2.0f;
        exponent--;
    }

    const float y = (value - 1.0f) / (value + 1.0f);
    const float y2 = y * y;
    float term = y;
    float sum = 0.0f;
    for (int n = 1; n <= 19; n += 2) {
        sum += term / (float)n;
        term *= y2;
    }

    return (2.0f * sum) + ((float)exponent * 0.69314718056f);
}

static bool
is_space_char(int c)
{
    return (c == ' ') || (c == '\t') || (c == '\n') ||
           (c == '\r') || (c == '\f') || (c == '\v');
}

static void
skip_file_space(FILE *file)
{
    int c;
    do {
        c = fgetc(file);
    } while ((c != EOF) && is_space_char(c));

    if (c != EOF) {
        ungetc(c, file);
    }
}

static bool
read_token(FILE *file, char *buffer, int buffer_size)
{
    skip_file_space(file);

    int c = fgetc(file);
    if (c == EOF) {
        buffer[0] = '\0';
        return false;
    }

    int count = 0;
    while ((c != EOF) && !is_space_char(c)) {
        if (count + 1 < buffer_size) {
            buffer[count++] = (char)c;
        }
        c = fgetc(file);
    }

    buffer[count] = '\0';
    return count > 0;
}

static int
parse_int_token(const char *token)
{
    int sign = 1;
    int index = 0;
    int base = 10;
    int value = 0;

    if (token[index] == '-') {
        sign = -1;
        index++;
    } else if (token[index] == '+') {
        index++;
    }

    if ((token[index] == '0') &&
        ((token[index + 1] == 'x') || (token[index + 1] == 'X'))) {
        base = 16;
        index += 2;
    }

    for (; token[index] != '\0'; index++) {
        int digit = -1;
        if ((token[index] >= '0') && (token[index] <= '9')) {
            digit = token[index] - '0';
        } else if ((token[index] >= 'a') && (token[index] <= 'f')) {
            digit = token[index] - 'a' + 10;
        } else if ((token[index] >= 'A') && (token[index] <= 'F')) {
            digit = token[index] - 'A' + 10;
        } else {
            break;
        }

        if (digit >= base) {
            break;
        }
        value = (value * base) + digit;
    }

    return value * sign;
}

static double
pow10_int(int exponent)
{
    double value = 1.0;
    if (exponent >= 0) {
        for (int i = 0; i < exponent; i++) {
            value *= 10.0;
        }
    } else {
        for (int i = 0; i < -exponent; i++) {
            value *= 0.1;
        }
    }
    return value;
}

static double
parse_float_token(const char *token)
{
    int sign = 1;
    int index = 0;
    double value = 0.0;

    if (token[index] == '-') {
        sign = -1;
        index++;
    } else if (token[index] == '+') {
        index++;
    }

    while ((token[index] >= '0') && (token[index] <= '9')) {
        value = (value * 10.0) + (double)(token[index] - '0');
        index++;
    }

    if (token[index] == '.') {
        index++;
        double scale = 0.1;
        while ((token[index] >= '0') && (token[index] <= '9')) {
            value += (double)(token[index] - '0') * scale;
            scale *= 0.1;
            index++;
        }
    }

    if ((token[index] == 'e') || (token[index] == 'E')) {
        index++;
        int exp_sign = 1;
        if (token[index] == '-') {
            exp_sign = -1;
            index++;
        } else if (token[index] == '+') {
            index++;
        }
        int exp_value = 0;
        while ((token[index] >= '0') && (token[index] <= '9')) {
            exp_value = (exp_value * 10) + (token[index] - '0');
            index++;
        }
        value *= pow10_int(exp_value * exp_sign);
    }

    return value * (double)sign;
}

extern "C" int
fscanf(FILE *file, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    int assigned = 0;
    char token[256];

    for (int i = 0; format[i] != '\0'; i++) {
        if (is_space_char(format[i])) {
            skip_file_space(file);
            continue;
        }

        if (format[i] != '%') {
            int c = fgetc(file);
            if (c != format[i]) {
                if (c != EOF) {
                    ungetc(c, file);
                }
                break;
            }
            continue;
        }

        i++;
        bool short_dest = false;
        if (format[i] == 'h') {
            short_dest = true;
            i++;
        } else if (format[i] == 'l') {
            i++;
        }

        const char spec = format[i];
        if (spec == '%') {
            int c = fgetc(file);
            if (c != '%') {
                if (c != EOF) {
                    ungetc(c, file);
                }
                break;
            }
            continue;
        }

        if (spec == 'i' || spec == 'd' || spec == 'u') {
            if (!read_token(file, token, sizeof(token))) {
                break;
            }
            const int value = parse_int_token(token);
            if (short_dest) {
                short *out = va_arg(args, short *);
                *out = (short)value;
            } else {
                int *out = va_arg(args, int *);
                *out = value;
            }
            assigned++;
        } else if (spec == 'f') {
            if (!read_token(file, token, sizeof(token))) {
                break;
            }
            float *out = va_arg(args, float *);
            *out = (float)parse_float_token(token);
            assigned++;
        } else if (spec == 's') {
            if (!read_token(file, token, sizeof(token))) {
                break;
            }
            char *out = va_arg(args, char *);
            int j = 0;
            while (token[j] != '\0') {
                out[j] = token[j];
                j++;
            }
            out[j] = '\0';
            assigned++;
        } else if (spec == 'c') {
            char *out = va_arg(args, char *);
            int c = fgetc(file);
            if (c == EOF) {
                break;
            }
            *out = (char)c;
            assigned++;
        }
    }

    va_end(args);
    return assigned;
}

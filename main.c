#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Tuple {
  int num;
  char str[4];
};


const struct Tuple datasheet[] = {
    {15840, "cGp"},
    {16465, "cmW"},
    {17941, "cX3"},
    {17942, "cXB"},
    {18898, "ctR"},
    {19172, "ckN"},
    {20512, "PVg"},
    {20626, "PD4"},
    {20758, "PBR"},
    {25736, "MYM"},
    {25893, "MSL"},
    {26039, "MUk"},
    {26134, "MIE"},
    {26345, "Mgr"},
    {26346, "MgK"},
    {26676, "MKd"},
    {28161, "GVT"},
    {31622, "vNx"},
    {31873, "vwP"},
    {32028, "vV9"},
    {35260, "zAj"},
    {36368, "zO9"},
    {36428, "zu1"},
    {38716, "AcO"},
    {38805, "APF"},
    {40111, "AHl"},
    {40893, "ALW"},
    {40956, "AQ9"},
    {40957, "AQs"},
    {40958, "AQq"},
    {40959, "AQL"},
    {40960, "AQQ"},
    {42541, "Zcz"},
    {47987, "yuk"},
    {49137, "yh2"},
    {49169, "yIi"},
    {49443, "yau"},
    {49444, "yap"},
    {49639, "ytL"},
    {50047, "T7T"},
    {50048, "T7N"},
    {50127, "Tx8"},
    {50128, "TxE"},
    {50129, "Tx2"},
    {51183, "Tn2"},
    {51184, "Tn1"},
    {51204, "Tnf"},
    {52071, "T2a"},
    {52977, "Thu"},
    {54650, "NTO"},
    {55908, "N2e"},
    {56100, "N9g"},
    {57924, "ocd"},
    {60538, "oeH"},
    {60539, "oe0"},
    {60540, "oeO"},
    {61474, "okE"},
    {63141, "dH6"},
    {64436, "dUw"},
    {64437, "dUn"},
    {67416, "m2D"},
    {72677, "wtT"},
    {73039, "nCi"},
    {73040, "nCc"},
    {73211, "nxJ"},
    {73654, "nzb"},
    {73756, "nZq"},
    {74037, "ndz"},
    {74038, "ndA"},
    {76081, "nIG"},
    {76082, "nIv"},
    {79467, "VXS"},
    {79564, "VYw"},
    {79790, "VeK"},
    {79791, "Vel"},
};


// Function to convert a given unsigned long number to a base62 string
char *num_to_base62(unsigned long num) {
    char base62_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    char *base62 = malloc(sizeof(char) * 12); // Maximum 12 characters in base62
    int i = 0;

    // Calculate the base62 string by finding the remainder when divided by 62
    while (num > 0) {
        int remainder = num % 62;
        base62[i++] = base62_chars[remainder];
        num /= 62;
    }
    base62[i] = '\0';

    // Reverse the base62 string to obtain the correct order
    char *reversed_base62 = malloc(sizeof(char) * (i + 2));
    int j = 0;
    for (int k = i - 1; k >= 0; k--) {
        reversed_base62[j++] = base62[k];
    }
    reversed_base62[j] = '\0';
    free(base62);
    return reversed_base62;
}


int main(void) {

    // Print the datasheet
    printf("Datasheet:\n");
    for (int i = 0; i < sizeof(datasheet) / sizeof(datasheet[0]); i++) {
        printf("%d %s\n", datasheet[i].num, datasheet[i].str);
    }
    printf("\n");

    // Define char_mapping dictionary here
    char char_mapping[64];
    memset(char_mapping, '\0', sizeof(char_mapping));
    for (int i = 0; i < sizeof(datasheet)/sizeof(datasheet[0]); i++) {
        char *base62 = num_to_base62(datasheet[i].num);
        for (int j = 0; j < strlen(base62); j++) {
            int index;
            if (base62[j] >= 'A' && base62[j] <= 'Z') {
                index = base62[j]-'A';
            } else if (base62[j] >= 'a' && base62[j] <= 'z') {
                index = base62[j]-'a'+26;
            } else {
                index = base62[j]-'0'+52;
            }
            char_mapping[index] = datasheet[i].str[j];
        }
        free(base62);
    }

    // Test the custom key map
    printf("Mapping test:\n");
    for (int i = 0; i < sizeof(datasheet) / sizeof(datasheet[0]); i++) {
        unsigned long a = datasheet[i].num;
        char *base62 = num_to_base62(a);
        char *mapped_str = malloc((strlen(base62) + 1) * sizeof(char));
        for (int j = 0; j < strlen(base62); j++) {
            int index;
            if (base62[j] >= 'A' && base62[j] <= 'Z') {
                index = base62[j]-'A';
            } else if (base62[j] >= 'a' && base62[j] <= 'z') {
                index = base62[j]-'a'+26;
            } else {
                index = base62[j]-'0'+52;
            }
            strncpy(mapped_str+j, &char_mapping[index], 1);
        }
        mapped_str[strlen(base62)] = '\0';
        printf("%s %s %s\n", base62, datasheet[i].str, mapped_str);
        free(base62);
        free(mapped_str);
    }


    // Q2 b) Find the output for the following inputs
    unsigned long inputs[] = {30001, 55555, 77788};
    size_t inputs_length = sizeof(inputs) / sizeof(inputs[0]);

    for (size_t i = 0; i < inputs_length; i++) {
        unsigned long a = inputs[i];
        char *base62 = num_to_base62(a);
        char *mapped_str = malloc((strlen(base62) + 1) * sizeof(char));
        for (int j = 0; j < strlen(base62); j++) {
            int index;
            if (base62[j] >= 'A' && base62[j] <= 'Z') {
                index = base62[j]-'A';
            } else if (base62[j] >= 'a' && base62[j] <= 'z') {
                index = base62[j]-'a'+26;
            } else {
                index = base62[j]-'0'+52;
            }
            strncpy(mapped_str+j, &char_mapping[index], 1);
        }
        mapped_str[strlen(base62)] = '\0';
        printf("f(%lu) = %s\n", a, mapped_str);
        free(base62);
        free(mapped_str);
    }


    // Q2 c) Calculate the maximum range without collisions or overflow
    int max_length = 0;
    for (int i = 0; i < sizeof(datasheet)/sizeof(datasheet[0]); i++) {
        int len = strlen(datasheet[i].str);
        if (len > max_length) {
            max_length = len;
        }
    }

    unsigned long long max_range = 1;
    for (int i = 0; i < max_length; i++) {
        max_range *= 62;
    }
    max_range -= 1; // Account for 0
    printf("Maximum range without collisions or overflow: %llu\n", max_range);

    return 0;
}
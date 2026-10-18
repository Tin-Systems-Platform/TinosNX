#ifndef KPRINT_H
#define KPRINT_H

class KPrint {
    public:
        static void kprint(const char* str);
        static void qemu_dbg(const char* str);
    private:
        static void print_char(char c); // Helper function to print a single character to the screen
};

#endif
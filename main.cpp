#include <iostream>
#include <sys/mman.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

void my_pause() {
    std::cout << "Press [Enter] to deallocate virtual memory...";
    std::cin.get();
}

int main() {
    size_t ONE_HUNDRED_TB = (size_t) 1024 * 1024 * 1024 * 1024 * 100;
    void *address = mmap(NULL, ONE_HUNDRED_TB, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (address == MAP_FAILED) {
        handle_error("mmap failed");
    }
    std::cout << "100Tb of virtual memory are allocated. Check in htop." << std::endl;
    my_pause();
    int code = munmap(address, ONE_HUNDRED_TB);
    if (code != 0) {
        handle_error("munmap failed");
    }
    return 0;
}
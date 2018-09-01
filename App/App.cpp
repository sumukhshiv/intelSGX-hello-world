#include <stdio.h>
#include <iostream>
#include "Enclave_u.h"
#include "sgx_urts.h"
#include "sgx_utils/sgx_utils.h"
#include <string>

#include <unistd.h>


/* Global EID shared by multiple threads */
sgx_enclave_id_t global_eid = 0;
sgx_enclave_id_t global_eid1 = 1;

// OCall implementations
void ocall_print(const char* str) {
    printf("%s\n", str);
}

int main(int argc, char const *argv[]) {


    if (initialize_enclave(&global_eid, "enclave.token", "enclave.signed.so") < 0) {
        std::cout << "Fail to initialize enclave." << std::endl;
        return 1;
    }

    if (initialize_enclave(&global_eid1, "enclave.token", "enclave.signed.so") < 0) {
        std::cout << "Fail to initialize enclave." << std::endl;
        return 1;
    }

    int hello_world_return;
    sgx_status_t status = hello_world(global_eid, &hello_world_return);
    if (hello_world_return == 0) {
      printf("Succesfully returned from hello_world inside enclave 0\n");
    }

    int world_hello_return;
    sgx_status_t status1 = hello_world(global_eid1, &world_hello_return);
    if (world_hello_return == 0) {
      printf("Succesfully returned from hello_world inside enclave 1\n");
    }



    return 0;

}

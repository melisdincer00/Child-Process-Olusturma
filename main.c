#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    // fork()--> child process olusturuyoruz
    pid = fork();

    if (pid < 0) {
        // fork basarisiz oldu
        perror("Fork basarisiz");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process: Dosya icin cat komutu calisiyor...\n");

        // cat komutunu �alistirmak icin
        execlp("cat", "cat", "dosya.txt", NULL);

        // execlp basarisiz olursa
        perror("execlp basarisiz");
        exit(1);
    } else {
        // Parent process
        printf("Parent process: Child process'in tamamlanmasi bekleniyor...\n");

        // wait()--> child process'in bitmesini bekliyoruz
        if (wait(&status) == -1) {
            perror("wait basarisiz");
            exit(1);
        }

        // �ikis durumunu kontrol etmek icin
        if (WIFEXITED(status)) {
            printf("Parent process: Child process basarili bir sekilde sonlandi, cikis kodu: %d\n", WEXITSTATUS(status));
        } else {
            printf("Parent process: Child process hatali sonlandi .\n");
        }
    }

    return 0;
}

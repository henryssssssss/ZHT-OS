#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];

void* philosopher(void* num) {
    int id = *(int*)num;
    while (1) {
        // 思考
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);
        // 请求筷子（遵循顺序避免死锁：奇数哲学家先左后右，偶数相反）
        if (id % 2 == 0) {
            sem_wait(&forks[id]);
            sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        } else {
            sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);
            sem_wait(&forks[id]);
        }
        // 进餐
        printf("Philosopher %d is eating.\n", id);
        sleep(2);
        // 释放筷子
        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % NUM_PHILOSOPHERS]);
    }
    return NULL;
}

int main() {
    int ids[NUM_PHILOSOPHERS];
    // 初始化信号量
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        sem_init(&forks[i], 0, 1);
    }
    // 创建哲学家线程
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }
    // 等待哲学家线程结束
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    // 销毁信号量
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }
    return 0;
}

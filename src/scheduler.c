#include <stdlib.h>
#include "../include/scheduler.h"


Scheduler* create_scheduler(int capacity){
    Scheduler* new_schedule = (Scheduler*)malloc(sizeof(Scheduler));
    if(new_schedule == NULL){
        return NULL;
    }

    new_schedule->process_queue =  heap_create(capacity, sizeof(Process), compare_vruntime);
    if (new_schedule->process_queue == NULL) {
        free(new_schedule);
        return NULL;
    }

    new_schedule->current_process = NULL;
    new_schedule->time_slice = 10;
    
    return new_schedule;
}

void destroy_scheduler(Scheduler* scheduler){
    if(scheduler == NULL){
        return;
    }

    if(scheduler->current_process){
        free(scheduler->current_process);
        scheduler->current_process = NULL;
    }

    if(scheduler->process_queue){
        heap_destroy(scheduler->process_queue);
        scheduler->process_queue = NULL;
    }

    free(scheduler);
}

void schedule_process(Scheduler* scheduler, Process process){
    if(scheduler == NULL || scheduler->process_queue == NULL) return;

    heap_insert(scheduler->process_queue, &process);
}

Process* get_next_process(Scheduler* scheduler) {
    if(scheduler == NULL || scheduler->process_queue == NULL) {
        return NULL;
    }

    if(scheduler->current_process != NULL) {
        heap_insert(scheduler->process_queue, scheduler->current_process);
        free(scheduler->current_process);
        scheduler->current_process = NULL;
    }

    Process* result = malloc(sizeof(Process));
    if(result == NULL) return NULL;

    if(heap_extract_min(scheduler->process_queue, result) < 0) {
        free(result);
        return NULL;
    }

    scheduler->current_process = result;
    result->is_running = true;
    return result;
}

void tick(Scheduler* scheduler) {
    if(scheduler == NULL || scheduler->current_process == NULL) {
        return;
    }
    update_vruntime(scheduler->current_process, scheduler->time_slice);
}
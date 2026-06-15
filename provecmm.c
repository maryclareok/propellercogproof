#include "simpletools.h"
#include "propeller.h"

#define STACK_SIZE 64

extern unsigned int _load_start_dummy_cog[];
extern unsigned int _load_start_provecmm_cog[];

typedef struct {
    volatile unsigned release_monitor;
    volatile unsigned monitor_started;
    volatile unsigned main_cogid;
    volatile unsigned monitor_cogid;
    volatile unsigned debug_stage;
} mailbox_t;

typedef struct {
    unsigned stack[STACK_SIZE];
    mailbox_t mailbox;
} cogdata_t;

static cogdata_t dummy_data;
static cogdata_t monitor_data;

int main(void)
{
    int dummy_cog;
    int monitor_cog;

    /* Initialize the dummy worker mailbox. */
    dummy_data.mailbox.release_monitor = 1;
    dummy_data.mailbox.monitor_started = 0;
    dummy_data.mailbox.main_cogid = cogid();
    dummy_data.mailbox.monitor_cogid = 999;
    dummy_data.mailbox.debug_stage = 1;

    /* Initialize the provecmm worker mailbox. */
    monitor_data.mailbox.release_monitor = 1;
    monitor_data.mailbox.monitor_started = 0;
    monitor_data.mailbox.main_cogid = cogid();
    monitor_data.mailbox.monitor_cogid = 999;
    monitor_data.mailbox.debug_stage = 1;

    print("Main cog ID: %u\n", cogid());

    /* Start dummy.cogc. */
    dummy_cog = cognew(
        _load_start_dummy_cog,
        &dummy_data.mailbox
    );

    if (dummy_cog < 0) {
        print("Failed to start dummy cog.\n");
        while (1);
    }

    print("cognew returned for dummy: %d\n", dummy_cog);

    /* Wait until dummy.cogc reports that it has started. */
    while (dummy_data.mailbox.monitor_started == 0) {
        waitcnt(CNT + 80000);
    }

    print(
        "Dummy worker reported cog ID: %u\n",
        dummy_data.mailbox.monitor_cogid
    );

    /* Start provecmm.cogc. */
    monitor_cog = cognew(
        _load_start_provecmm_cog,
        &monitor_data.mailbox
    );

    if (monitor_cog < 0) {
        print("Failed to start provecmm cog.\n");
        while (1);
    }

    print("cognew returned for provecmm: %d\n", monitor_cog);

    /* Wait until provecmm.cogc reports that it has started. */
    while (monitor_data.mailbox.monitor_started == 0) {
        waitcnt(CNT + 80000);
    }

    print(
        "Provecmm worker reported cog ID: %u\n",
        monitor_data.mailbox.monitor_cogid
    );

    print(
        "Dummy debug stage: %u\n",
        dummy_data.mailbox.debug_stage
    );

    print(
        "Provecmm debug stage: %u\n",
        monitor_data.mailbox.debug_stage
    );

    while (1) {
        waitcnt(CNT + 80000);
    }

    return 0;
}
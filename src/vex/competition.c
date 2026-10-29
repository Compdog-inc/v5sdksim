#include "vex/v5.h"

static uint32_t competition_status = 0;

uint32_t vexCompetitionStatus(void)
{
    return competition_status;
}

void vexSimCompetitionStatusSet(uint32_t status)
{
    competition_status = status;
}

void vexCompetitionControl(uint32_t data)
{
    // TODO: implement
}
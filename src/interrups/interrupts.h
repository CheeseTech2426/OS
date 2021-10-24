#pragma once
#include "../BasicRenderer.h"

struct interrupt_frame;

__attribute__((interrupt)) void PageFauld_Handler(struct interrupt_frame* frame);

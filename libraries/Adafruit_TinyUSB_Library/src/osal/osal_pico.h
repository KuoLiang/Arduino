/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the TinyUSB stack.
 */

<<<<<<< Updated upstream
#ifndef TUSB_OSAL_PICO_H_
#define TUSB_OSAL_PICO_H_
=======
#ifndef _TUSB_OSAL_PICO_H_
#define _TUSB_OSAL_PICO_H_
>>>>>>> Stashed changes

#include "pico/time.h"
#include "pico/sem.h"
#include "pico/mutex.h"
#include "pico/critical_section.h"

#ifdef __cplusplus
<<<<<<< Updated upstream
extern "C" {
=======
 extern "C" {
>>>>>>> Stashed changes
#endif

//--------------------------------------------------------------------+
// TASK API
//--------------------------------------------------------------------+
<<<<<<< Updated upstream
TU_ATTR_ALWAYS_INLINE static inline void osal_task_delay(uint32_t msec) {
=======
TU_ATTR_ALWAYS_INLINE static inline void osal_task_delay(uint32_t msec)
{
>>>>>>> Stashed changes
  sleep_ms(msec);
}

//--------------------------------------------------------------------+
// Binary Semaphore API
//--------------------------------------------------------------------+
<<<<<<< Updated upstream
typedef struct semaphore osal_semaphore_def_t, * osal_semaphore_t;

TU_ATTR_ALWAYS_INLINE static inline osal_semaphore_t osal_semaphore_create(osal_semaphore_def_t* semdef) {
=======
typedef struct semaphore osal_semaphore_def_t, *osal_semaphore_t;

TU_ATTR_ALWAYS_INLINE static inline osal_semaphore_t osal_semaphore_create(osal_semaphore_def_t* semdef)
{
>>>>>>> Stashed changes
  sem_init(semdef, 0, 255);
  return semdef;
}

<<<<<<< Updated upstream
TU_ATTR_ALWAYS_INLINE static inline bool osal_semaphore_delete(osal_semaphore_t semd_hdl) {
  (void) semd_hdl;
  return true; // nothing to do
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_semaphore_post(osal_semaphore_t sem_hdl, bool in_isr) {
=======
TU_ATTR_ALWAYS_INLINE static inline bool osal_semaphore_post(osal_semaphore_t sem_hdl, bool in_isr)
{
>>>>>>> Stashed changes
  (void) in_isr;
  sem_release(sem_hdl);
  return true;
}

<<<<<<< Updated upstream
TU_ATTR_ALWAYS_INLINE static inline bool osal_semaphore_wait(osal_semaphore_t sem_hdl, uint32_t msec) {
  return sem_acquire_timeout_ms(sem_hdl, msec);
}

TU_ATTR_ALWAYS_INLINE static inline void osal_semaphore_reset(osal_semaphore_t sem_hdl) {
=======
TU_ATTR_ALWAYS_INLINE static inline bool osal_semaphore_wait (osal_semaphore_t sem_hdl, uint32_t msec)
{
  return sem_acquire_timeout_ms(sem_hdl, msec);
}

TU_ATTR_ALWAYS_INLINE static inline void osal_semaphore_reset(osal_semaphore_t sem_hdl)
{
>>>>>>> Stashed changes
  sem_reset(sem_hdl, 0);
}

//--------------------------------------------------------------------+
// MUTEX API
// Within tinyusb, mutex is never used in ISR context
//--------------------------------------------------------------------+
<<<<<<< Updated upstream
typedef struct mutex osal_mutex_def_t, * osal_mutex_t;

TU_ATTR_ALWAYS_INLINE static inline osal_mutex_t osal_mutex_create(osal_mutex_def_t* mdef) {
=======
typedef struct mutex osal_mutex_def_t, *osal_mutex_t;

TU_ATTR_ALWAYS_INLINE static inline osal_mutex_t osal_mutex_create(osal_mutex_def_t* mdef)
{
>>>>>>> Stashed changes
  mutex_init(mdef);
  return mdef;
}

<<<<<<< Updated upstream
TU_ATTR_ALWAYS_INLINE static inline bool osal_mutex_delete(osal_mutex_t mutex_hdl) {
  (void) mutex_hdl;
  return true; // nothing to do
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_mutex_lock(osal_mutex_t mutex_hdl, uint32_t msec) {
  return mutex_enter_timeout_ms(mutex_hdl, msec);
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_mutex_unlock(osal_mutex_t mutex_hdl) {
=======
TU_ATTR_ALWAYS_INLINE static inline bool osal_mutex_lock (osal_mutex_t mutex_hdl, uint32_t msec)
{
  return mutex_enter_timeout_ms(mutex_hdl, msec);
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_mutex_unlock(osal_mutex_t mutex_hdl)
{
>>>>>>> Stashed changes
  mutex_exit(mutex_hdl);
  return true;
}

//--------------------------------------------------------------------+
// QUEUE API
//--------------------------------------------------------------------+
#include "common/tusb_fifo.h"

<<<<<<< Updated upstream
typedef struct {
  tu_fifo_t ff;
  struct critical_section critsec; // osal_queue may be used in IRQs, so need critical section
=======
typedef struct
{
    tu_fifo_t ff;
    struct critical_section critsec; // osal_queue may be used in IRQs, so need critical section
>>>>>>> Stashed changes
} osal_queue_def_t;

typedef osal_queue_def_t* osal_queue_t;

// role device/host is used by OS NONE for mutex (disable usb isr) only
<<<<<<< Updated upstream
#define OSAL_QUEUE_DEF(_int_set, _name, _depth, _type)    \
=======
#define OSAL_QUEUE_DEF(_int_set, _name, _depth, _type)       \
>>>>>>> Stashed changes
  uint8_t _name##_buf[_depth*sizeof(_type)];              \
  osal_queue_def_t _name = {                              \
    .ff = TU_FIFO_INIT(_name##_buf, _depth, _type, false) \
  }

<<<<<<< Updated upstream
TU_ATTR_ALWAYS_INLINE static inline osal_queue_t osal_queue_create(osal_queue_def_t* qdef) {
=======
// lock queue by disable USB interrupt
TU_ATTR_ALWAYS_INLINE static inline void _osal_q_lock(osal_queue_t qhdl)
{
  critical_section_enter_blocking(&qhdl->critsec);
}

// unlock queue
TU_ATTR_ALWAYS_INLINE static inline void _osal_q_unlock(osal_queue_t qhdl)
{
  critical_section_exit(&qhdl->critsec);
}

TU_ATTR_ALWAYS_INLINE static inline osal_queue_t osal_queue_create(osal_queue_def_t* qdef)
{
>>>>>>> Stashed changes
  critical_section_init(&qdef->critsec);
  tu_fifo_clear(&qdef->ff);
  return (osal_queue_t) qdef;
}

<<<<<<< Updated upstream
TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_delete(osal_queue_t qhdl) {
  osal_queue_def_t* qdef = (osal_queue_def_t*) qhdl;
  critical_section_deinit(&qdef->critsec);
  return true;
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_receive(osal_queue_t qhdl, void* data, uint32_t msec) {
  (void) msec; // not used, always behave as msec = 0

  critical_section_enter_blocking(&qhdl->critsec);
  bool success = tu_fifo_read(&qhdl->ff, data);
  critical_section_exit(&qhdl->critsec);
=======
TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_receive(osal_queue_t qhdl, void* data, uint32_t msec)
{
  (void) msec; // not used, always behave as msec = 0

  // TODO: revisit... docs say that mutexes are never used from IRQ context,
  //  however osal_queue_recieve may be. therefore my assumption is that
  //  the fifo mutex is not populated for queues used from an IRQ context
  //assert(!qhdl->ff.mutex);

  _osal_q_lock(qhdl);
  bool success = tu_fifo_read(&qhdl->ff, data);
  _osal_q_unlock(qhdl);
>>>>>>> Stashed changes

  return success;
}

<<<<<<< Updated upstream
TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_send(osal_queue_t qhdl, void const* data, bool in_isr) {
  (void) in_isr;

  critical_section_enter_blocking(&qhdl->critsec);
  bool success = tu_fifo_write(&qhdl->ff, data);
  critical_section_exit(&qhdl->critsec);
=======
TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_send(osal_queue_t qhdl, void const * data, bool in_isr)
{
  // TODO: revisit... docs say that mutexes are never used from IRQ context,
  //  however osal_queue_recieve may be. therefore my assumption is that
  //  the fifo mutex is not populated for queues used from an IRQ context
  //assert(!qhdl->ff.mutex);
  (void) in_isr;

  _osal_q_lock(qhdl);
  bool success = tu_fifo_write(&qhdl->ff, data);
  _osal_q_unlock(qhdl);

  TU_ASSERT(success);
>>>>>>> Stashed changes

  return success;
}

<<<<<<< Updated upstream
TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_empty(osal_queue_t qhdl) {
=======
TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_empty(osal_queue_t qhdl)
{
>>>>>>> Stashed changes
  // TODO: revisit; whether this is true or not currently, tu_fifo_empty is a single
  //  volatile read.

  // Skip queue lock/unlock since this function is primarily called
  // with interrupt disabled before going into low power mode
  return tu_fifo_empty(&qhdl->ff);
}

#ifdef __cplusplus
<<<<<<< Updated upstream
}
#endif

#endif
=======
 }
#endif

#endif /* _TUSB_OSAL_PICO_H_ */
>>>>>>> Stashed changes

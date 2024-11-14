/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Tian Yunhao (t123yh)
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
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
#ifndef TUSB_OSAL_RTX4_H_
#define TUSB_OSAL_RTX4_H_
=======
#ifndef _TUSB_OSAL_RTX4_H_
#define _TUSB_OSAL_RTX4_H_
>>>>>>> Stashed changes

#include <rtl.h>

#ifdef __cplusplus
extern "C" {
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
  uint16_t hi = msec >> 16;
  uint16_t lo = msec;
  while (hi--) {
    os_dly_wait(0xFFFE);
  }
  os_dly_wait(lo);
}

TU_ATTR_ALWAYS_INLINE static inline uint16_t msec2wait(uint32_t msec) {
<<<<<<< Updated upstream
  if (msec == OSAL_TIMEOUT_WAIT_FOREVER) {
    return 0xFFFF;
  } else if (msec >= 0xFFFE) {
    return 0xFFFE;
  } else {
    return msec;
  }
=======
  if (msec == OSAL_TIMEOUT_WAIT_FOREVER)
    return 0xFFFF;
  else if (msec >= 0xFFFE)
    return 0xFFFE;
  else
    return msec;
>>>>>>> Stashed changes
}

//--------------------------------------------------------------------+
// Semaphore API
//--------------------------------------------------------------------+
typedef OS_SEM osal_semaphore_def_t;
typedef OS_ID osal_semaphore_t;

TU_ATTR_ALWAYS_INLINE static inline OS_ID osal_semaphore_create(osal_semaphore_def_t* semdef) {
  os_sem_init(semdef, 0);
  return semdef;
}

<<<<<<< Updated upstream
TU_ATTR_ALWAYS_INLINE static inline bool osal_semaphore_delete(osal_semaphore_t semd_hdl) {
  (void) semd_hdl;
  return true; // nothing to do
}

=======
>>>>>>> Stashed changes
TU_ATTR_ALWAYS_INLINE static inline bool osal_semaphore_post(osal_semaphore_t sem_hdl, bool in_isr) {
  if ( !in_isr ) {
    os_sem_send(sem_hdl);
  } else {
    isr_sem_send(sem_hdl);
  }
	return true;
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_semaphore_wait (osal_semaphore_t sem_hdl, uint32_t msec) {
  return os_sem_wait(sem_hdl, msec2wait(msec)) != OS_R_TMO;
}

TU_ATTR_ALWAYS_INLINE static inline void osal_semaphore_reset(osal_semaphore_t const sem_hdl) {
  // TODO: implement
}

//--------------------------------------------------------------------+
// MUTEX API (priority inheritance)
//--------------------------------------------------------------------+
typedef OS_MUT osal_mutex_def_t;
typedef OS_ID osal_mutex_t;

<<<<<<< Updated upstream
TU_ATTR_ALWAYS_INLINE static inline osal_mutex_t osal_mutex_create(osal_mutex_def_t* mdef) {
=======
TU_ATTR_ALWAYS_INLINE static inline osal_mutex_t osal_mutex_create(osal_mutex_def_t* mdef)
{
>>>>>>> Stashed changes
  os_mut_init(mdef);
  return mdef;
}

<<<<<<< Updated upstream
TU_ATTR_ALWAYS_INLINE static inline bool osal_mutex_delete(osal_mutex_t mutex_hdl) {
  (void) mutex_hdl;
  return true; // nothing to do
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_mutex_lock (osal_mutex_t mutex_hdl, uint32_t msec) {
  return os_mut_wait(mutex_hdl, msec2wait(msec)) != OS_R_TMO;
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_mutex_unlock(osal_mutex_t mutex_hdl) {
=======
TU_ATTR_ALWAYS_INLINE static inline bool osal_mutex_lock (osal_mutex_t mutex_hdl, uint32_t msec)
{
  return os_mut_wait(mutex_hdl, msec2wait(msec)) != OS_R_TMO;
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_mutex_unlock(osal_mutex_t mutex_hdl)
{
>>>>>>> Stashed changes
  return os_mut_release(mutex_hdl) == OS_R_OK;
}

//--------------------------------------------------------------------+
// QUEUE API
//--------------------------------------------------------------------+

// role device/host is used by OS NONE for mutex (disable usb isr) only
#define OSAL_QUEUE_DEF(_int_set, _name, _depth, _type)   \
  os_mbx_declare(_name##__mbox, _depth);              \
  _declare_box(_name##__pool, sizeof(_type), _depth); \
  osal_queue_def_t _name = { .depth = _depth, .item_sz = sizeof(_type), .pool = _name##__pool, .mbox = _name##__mbox };

<<<<<<< Updated upstream
typedef struct {
=======

typedef struct
{
>>>>>>> Stashed changes
  uint16_t depth;
  uint16_t item_sz;
  U32* pool;
  U32* mbox;
}osal_queue_def_t;

typedef osal_queue_def_t* osal_queue_t;

<<<<<<< Updated upstream
TU_ATTR_ALWAYS_INLINE static inline osal_queue_t osal_queue_create(osal_queue_def_t* qdef) {
=======
TU_ATTR_ALWAYS_INLINE static inline osal_queue_t osal_queue_create(osal_queue_def_t* qdef)
{
>>>>>>> Stashed changes
  os_mbx_init(qdef->mbox, (qdef->depth + 4) * 4);
  _init_box(qdef->pool, ((qdef->item_sz+3)/4)*(qdef->depth) + 3, qdef->item_sz);
  return qdef;
}

<<<<<<< Updated upstream
TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_receive(osal_queue_t qhdl, void* data, uint32_t msec) {
=======
TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_receive(osal_queue_t qhdl, void* data, uint32_t msec)
{
>>>>>>> Stashed changes
  void* buf;
  os_mbx_wait(qhdl->mbox, &buf, msec2wait(msec));
  memcpy(data, buf, qhdl->item_sz);
  _free_box(qhdl->pool, buf);
  return true;
}

<<<<<<< Updated upstream
TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_delete(osal_queue_t qhdl) {
  (void) qhdl;
  return true; // nothing to do ?
}

TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_send(osal_queue_t qhdl, void const * data, bool in_isr) {
  void* buf = _alloc_box(qhdl->pool);
  memcpy(buf, data, qhdl->item_sz);
  if ( !in_isr ) {
    os_mbx_send(qhdl->mbox, buf, 0xFFFF);
  } else {
=======
TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_send(osal_queue_t qhdl, void const * data, bool in_isr)
{
  void* buf = _alloc_box(qhdl->pool);
  memcpy(buf, data, qhdl->item_sz);
  if ( !in_isr )
  {
    os_mbx_send(qhdl->mbox, buf, 0xFFFF);
  }
  else
  {
>>>>>>> Stashed changes
    isr_mbx_send(qhdl->mbox, buf);
  }
  return true;
}

<<<<<<< Updated upstream
TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_empty(osal_queue_t qhdl) {
=======
TU_ATTR_ALWAYS_INLINE static inline bool osal_queue_empty(osal_queue_t qhdl)
{
>>>>>>> Stashed changes
  return os_mbx_check(qhdl->mbox) == qhdl->depth;
}

#ifdef __cplusplus
 }
#endif

#endif

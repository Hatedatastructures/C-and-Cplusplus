#pragma once
#include "concurrent_map.hpp"
#include "concurrent_set.hpp"
#include "concurrent_list.hpp"
#include "concurrent_deque.hpp"
#include "concurrent_stack.hpp"
#include "concurrent_queue.hpp"
#include "concurrent_array.hpp"
#include "concurrent_bitset.hpp"
#include "concurrent_string.hpp"
#include "concurrent_vector.hpp"
#include "concurrent_multimap.hpp"
#include "concurrent_multiset.hpp"
#include "concurrent_forward_list.hpp"
#include "concurrent_annular_queue.hpp"
#include "concurrent_unordered_map.hpp"
#include "concurrent_unordered_set.hpp"
#include "concurrent_priority_queue.hpp"
#include "concurrent_unordered_multimap.hpp"
#include "concurrent_unordered_multiset.hpp"


namespace wan
{
  /**
 * @namespace thread_pool::concurrent_containers
 * 
 * @brief 线程安全并发容器命名空间
 * 
 * 该命名空间包含一系列线程安全的并发容器实现，基于`C++`标准库容器封装，提供多生产者-多消费者场景下的安全访问接口
 * 
 * 包含的核心容器类型：
 * 
 *   - 序列容器：`concurrent_vector`、`concurrent_array`、`concurrent_list`、`concurrent_forward_list`
 * 
 *   - 关联容器：`concurrent_set`、`concurrent_map`、`concurrent_multiset`、`concurrent_multimap`
 * 
 *   - 无序关联容器：`concurrent_unordered_set`、`concurrent_unordered_map`、`concurrent_unordered_multiset`、`concurrent_unordered_multimap`
 * 
 *   - 容器适配器：`concurrent_queue`、`concurrent_stack`、`concurrent_priority_queue`
 * 
 *   - 特殊容器：`concurrent_bitset`、`concurrent_string`
 * 
 * @warning 大部分容器都会自动扩容，因此需要合理设置容器初始大小以避免频繁扩容带来的性能开销
 * 
 * @note 容器迭代器均为只读迭代器（`const_iterator`），避免外部修改破坏内部一致性；
 *       所有修改操作（如`insert`、`erase`）均会触发同步机制，导致性能开销，
 *       高并发场景下建议批量操作以减少锁竞争。
 */
  namespace mco = multi_concurrent;
}
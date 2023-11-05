#pragma once

#include <memory>
#include <optional>
#include <vector>

namespace Gp {

  template<typename T>
  class RingBuffer {
  public:
    RingBuffer() = default;

    void initialize(size_t size) {
      m_head = 0;
      m_tail = 0;
      m_buffer.resize(size + 1);
      m_bufferSize = size;
    }

    /*!
     * Return whether the buffer is empty.
     */
    bool isEmpty() const {
      return m_head == m_tail;
    }

    // Return whether the buffer is full.
    bool isFull() const {
      return next(m_tail) == m_head;
    }

    // Push a value into the ring buffer.
    bool push(T value) {
      if (isFull()) {
        return false;
      }
      m_buffer[m_tail] = std::move(value);
      m_tail = next(m_tail);
      return true;
    }

    // Fetch a value from ring buffer.
    std::optional<T> pop() {
      if (isEmpty()) {
        return {};
      }
      T result = std::move(m_buffer[m_head]);
      m_head = next(m_head);
      return result;
    }

  private:
    std::vector<T> m_buffer;
    std::atomic<size_t> m_head, m_tail;
    size_t m_bufferSize;

    size_t next(size_t current) const {
      return (current + 1) % m_bufferSize;
    }
  };
}

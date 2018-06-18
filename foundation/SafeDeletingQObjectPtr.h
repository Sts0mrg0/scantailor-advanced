/*
    Scan Tailor - Interactive post-processing tool for scanned pages.
    Copyright (C) 2007-2009  Joseph Artsimovich <joseph_a@mail.ru>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SAFE_DELETING_QOBJECT_PTR_H_
#define SAFE_DELETING_QOBJECT_PTR_H_

#include "NonCopyable.h"

template <typename T>
class SafeDeletingQObjectPtr {
  DECLARE_NON_COPYABLE(SafeDeletingQObjectPtr)

 public:
  explicit SafeDeletingQObjectPtr(T* obj = 0) : m_obj(obj) {}

  ~SafeDeletingQObjectPtr() {
    if (m_obj) {
      m_obj->disconnect();
      m_obj->deleteLater();
    }
  }

  void reset(T* other) { SafeDeletingQObjectPtr(other).swap(*this); }

  T& operator*() const { return *m_obj; }

  T* operator->() const { return m_obj; }

  T* get() const { return m_obj; }

  void swap(SafeDeletingQObjectPtr& other) {
    T* tmp = m_obj;
    m_obj = other.m_obj;
    other.m_obj = tmp;
  }

 private:
  T* m_obj;
};


template <typename T>
void swap(SafeDeletingQObjectPtr<T>& o1, SafeDeletingQObjectPtr<T>& o2) {
  o1.swap(o2);
}

#endif  // ifndef SAFE_DELETING_QOBJECT_PTR_H_

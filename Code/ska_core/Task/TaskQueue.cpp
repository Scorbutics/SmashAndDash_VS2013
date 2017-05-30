#include "TaskQueue.h"
#include "Runnable.h"

ska::TaskQueue::TaskQueue() : m_previous(nullptr), m_current(nullptr) {
}

ska::Runnable& ska::TaskQueue::queueTask(RunnablePtr& t) {
	m_tasks.push(move(t));
	return *m_tasks.back();
}

bool ska::TaskQueue::hasRunningTask() const {
	return !m_tasks.empty();
}

void ska::TaskQueue::refresh() {
	if (m_current == nullptr) {
		m_current = m_tasks.empty() ? nullptr : move(m_tasks.front());
		if (m_current == nullptr) {
			return;
		}
		m_tasks.pop();
	}

	if (!(*m_current)()) {
		m_previous = move(m_current);
		m_current = nullptr;
	}
}

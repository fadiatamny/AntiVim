#ifndef EXECUTION_QUEUE_HPP
#define EXECUTION_QUEUE_HPP

#include <iostream>
#include <functional>
#include <queue>
#include <mutex>

class ExecutionQueue {
public:
    void push(std::function<void()> action) {
        std::lock_guard<std::mutex> lock(this->mutex);
        this->actions.push(action);
    }

    void execute() {
        while (!this->actions.empty()) {
            std::function<void()> action;
            {
                std::lock_guard<std::mutex> lock(this->mutex);
                if (!actions.empty()) {
                    action = this->actions.front();
                    this->actions.pop();
                }
            }

            if (action) {
                action();
            }
        }
    }

    bool hasActions() {
        std::lock_guard<std::mutex> lock(this->mutex);
        return !this->actions.empty();
    }

private:
    std::queue<std::function<void()>> actions;
    std::mutex mutex;
};


#endif // EXECUTION_QUEUE_HPP
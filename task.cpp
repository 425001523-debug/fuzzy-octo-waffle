#include "task.h"

Task::Task() {
    taskId = 0;
    title = "";
    subject = "";
    deadline = "";
    priorityLevel = 1;
    completed = false;
}

Task::Task(int id, string t, string sub, string due, int priority, bool status) {
    taskId = id;
    title = t;
    subject = sub;
    deadline = due;
    priorityLevel = priority;
    completed = status;
}

void Task::setTaskId(int id) { taskId = id; }
int Task::getTaskId() { return taskId; }

void Task::setTitle(string t) { title = t; }
string Task::getTitle() { return title; }

void Task::setSubject(string sub) { subject = sub; }
string Task::getSubject() { return subject; }

void Task::setDeadline(string due) { deadline = due; }
string Task::getDeadline() { return deadline; }

void Task::setPriorityLevel(int priority) { priorityLevel = priority; }
int Task::getPriorityLevel() { return priorityLevel; }

void Task::setCompleted(bool status) { completed = status; }
bool Task::isCompleted() { return completed; }

double Task::calculateProductivityScore() {
    double score = 100;
    if (!completed) {
        score -= 40;
    }
    score -= (priorityLevel * 5);
    return score;
}

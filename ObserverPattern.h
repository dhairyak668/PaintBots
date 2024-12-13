#pragma once
#include <vector>
#include <algorithm>

/**
 * @class Observer
 * @brief Abstract base class for observers in the Observer pattern.
 * 
 * The Observer class defines the interface for objects that should be notified of changes
 * in an Observable object. Subclasses must implement the update method to handle
 * notifications.
 */
class Observer {
public:
    virtual ~Observer() = default;

    /**
     * @brief Method to be called when the Observable object changes.
     * @param data A pointer to the data associated with the change.
     */
    virtual void update(void* data) = 0;
};

/**
 * @class Observable
 * @brief Base class for objects that can be observed by Observer objects.
 * 
 * The Observable class maintains a list of observers and notifies them of changes.
 * Observers can be added or removed from the list.
 */
class Observable {
private:
    std::vector<Observer*> observers; 

public:
    /**
     * @brief Adds an observer to the list.
     * @param observer A pointer to the observer to be added.
     */
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    /**
     * @brief Removes an observer from the list.
     * @param observer A pointer to the observer to be removed.
     */
    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    /**
     * @brief Gets the number of observers in the list.
     * @return The number of observers.
     */
    int getNumObservers() {
        return observers.size();
    }

protected:
    /**
     * @brief Notifies all observers of a change.
     * @param data A pointer to the data associated with the change.
     */
    void notifyObservers(void* data) {
        for (Observer* observer : observers) {
            observer->update(data);
        }
    }
};
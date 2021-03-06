/*
 * Copyright 2014 Patrick Kramer, Vincent Wassenaar
 *
 * This file is part of PowerGrid.
 *
 * PowerGrid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PowerGrid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PowerGrid.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <QObject>
#include "component/position.h"

namespace API {

class Navigator;

using component::Position;

/**
 * @brief Represents a Navigation path between two points.
 *
 * This class maintains a list of positions resembling a path,
 * as well as a current position along that path.
 */
class Navigation : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(Navigation)
private:
    QList<Position*> _path;
    int _current;
    mutable int _length;

    long computeLength() const;

    friend class Navigator;
public:
    /**
     * @brief Creates a new Navigation instance to navigate the specified path
     * @param path - the path to navigate, as a list of points.
     */
    explicit Navigation(QList<Position*> path);

    /**
     * @brief Returns the path of this Navigation
     * @return the path of this Navigation
     */
    QList<Position*> path() const { return _path; }
    /**
     * @brief Returns the current position in this Navigation
     * @return the current position
     */
    int currentPos() const { return _current; }

    /**
     * @brief Returns the progress of this path
     *
     * The returned result expresses the approximate
     * progress as a value between 0.0 and 1.0.
     *
     * The returned value may never become 1.0, so this function should
     * not be used to check for completion. Use the appropriate functions
     * and/or signals in the Navigator class instead.
     *
     * @return a value between 0.0 and 1.0 indicating the progress.
     */
    double progress() const { return double(_current) / _path.length(); }
    /**
     * @brief Returns the approximate length of the path, in world units
     *
     * This is not the definite length, but an approximation. The actual
     * length of the path depends on the path chosen by the RS client.
     *
     * Computing the length is a relatively time-consuming operation. As such,
     * the result of this computation is cached for quick retrieval later. This
     * has as an effect, that the first time this function is called, it may take
     * more time to complete (depending on the amount of points on the path).
     *
     * @return the approximate length of the path
     */
    long length() const;
protected:
    /**
     * @brief Returns whether more elements remain on this path
     * @return true if (and only if) there are more elements on this path
     */
    bool hasNext() const;
    /**
     * @brief Returns the next element on this path
     * @return the next element
     */
    Position* next();
    /**
     * @brief Returns the current element
     * @return the current element
     */
    Position* current() const;

signals:
    /**
     * @brief Signal emitted whenever a position on the path is reached.
     *
     * @param position - the next position in the sequence
     */
    void progress(Position* position);
public slots:
    /**
     * @brief Resets this Navigation
     *
     * This causes the Navigation instance to start again at the first
     * position on the path.
     *
     * Calling this function while this Navigation is being executed may
     * have undesired effects, and as such is discouraged.
     */
    void reset();
};

}

#endif // NAVIGATION_H

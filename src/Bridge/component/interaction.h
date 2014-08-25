#ifndef COMPONENT_INTERACTION_H
#define COMPONENT_INTERACTION_H

#include "entity/component.h"
#include <QMap>

using entity::Component;

namespace component {

class Action;

/**
 * \brief Adds interactions to an Entity.
 *
 * This Component type can be used to assign actions to Entities.
 * These actions can relate to actual actions available in the
 * Runescape client, or actions added by PowerGrid (or any of its Plugins).
 */
class Interaction : public Component {
    Q_OBJECT
    Q_DISABLE_COPY(Interaction)
private:
    QMap<QString, Action*> actions;
public:
    /**
     * @brief Creates a new Interaction Component
     * @param _actions the actions that can be performed
     * @param parent [optional] - the parent of this Component
     */
    explicit Interaction(QMap<QString, Action*> _actions,
                         entity::Entity *parent = 0);

    /**
     * @brief Returns the Action* with the given name.
     *
     * If no Action exists with that name, a NULL pointer is
     * returned.
     * @param name the name of the requested Action
     * @return the Action, or NULL if it doesn't exist.
     */
    Action* getAction(QString name) const;
    /**
     * @brief Returns a QMap with all available Actions
     *
     * The returned QMap maps the name of the Action to the
     * Action*.
     * @return a QMap with the available Actions.
     */
    QMap<QString, Action*> getActionMap() const;

};
} // namespace component

#endif // COMPONENT_INTERACTION_H

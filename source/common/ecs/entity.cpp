#include "entity.hpp"
#include "../deserialize-utils.hpp"
#include "../components/component-deserializer.hpp"

#include <glm/gtx/euler_angles.hpp>

namespace our {

    // This function returns the transformation matrix from the entity's local space to the world space
    // Remember that you can get the transformation matrix from this entity to its parent from "localTransform"
    // To get the local to world matrix, you need to combine this entities matrix with its parent's matrix and
    // its parent's parent's matrix and so on till you reach the root.
    glm::mat4 Entity::getLocalToWorldMatrix() const {
        //TODO: Write this function
        // if already at world, return identity
        if (parent == nullptr) {
            return localTransform.toMat4();
        }

        // if not at world, get the proper transform
        glm::mat4 localToWorld = localTransform.toMat4();
        Entity* temp_parent = parent;
        while (temp_parent != nullptr) {
            localToWorld = temp_parent->localTransform.toMat4() * localToWorld;
            temp_parent = temp_parent->parent;
        }

        return localToWorld;
    }

    // Deserializes the entity data and components from a json object
    void Entity::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        name = data.value("name", name);
        tag = data.value("tag", "");
        localTransform.deserialize(data);
        if(data.contains("components")){
            if(const auto& components = data["components"]; components.is_array()){
                for(auto& component: components){
                    deserializeComponent(component, this);
                }
            }
        }
    }

}
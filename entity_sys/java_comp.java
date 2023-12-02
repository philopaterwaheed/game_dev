import java.util.HashMap;
import java.util.Map;

// Component interface
interface Component {
    // Common methods for all components
}

// Example components
class PositionComponent implements Component {
    int x, y;

    public PositionComponent(int x, int y) {
        this.x = x;
        this.y = y;
    }
}

class RenderComponent implements Component {
    String texture;

    public RenderComponent(String texture) {
        this.texture = texture;
    }
}

// Entity class
class Entity {
    int id;
    Map<Class<? extends Component>, Component> components = new HashMap<>();

    public Entity(int id) {
        this.id = id;
    }

    public void addComponent(Component component) {
        components.put(component.getClass(), component);
    }

    public <T extends Component> T getComponent(Class<T> componentClass) {
        return componentClass.cast(components.get(componentClass));
    }
}

// EntityManager class
class EntityManager {
    private Map<Integer, Entity> entities = new HashMap<>();
    private int nextEntityId = 1;

    public Entity createEntity() {
        Entity entity = new Entity(nextEntityId++);
        entities.put(entity.id, entity);
        return entity;
    }

    public Entity getEntity(int entityId) {
        return entities.get(entityId);
    }

    public void removeEntity(int entityId) {
        entities.remove(entityId);
    }
}

public class GameEntitySystem {
    public static void main(String[] args) {
        // Create an entity manager
        EntityManager entityManager = new EntityManager();

        // Create entities
        Entity player = entityManager.createEntity();
        Entity enemy = entityManager.createEntity();

        // Add components to entities
        player.addComponent(new PositionComponent(10, 20));
        player.addComponent(new RenderComponent("player_texture"));

        enemy.addComponent(new PositionComponent(30, 40));
        enemy.addComponent(new RenderComponent("enemy_texture"));

        // Access components of entities
        PositionComponent playerPosition = player.getComponent(PositionComponent.class);
        if (playerPosition != null) {
            System.out.println("Player Position: (" + playerPosition.x + ", " + playerPosition.y + ")");
        }

        RenderComponent enemyRender = enemy.getComponent(RenderComponent.class);
        if (enemyRender != null) {
            System.out.println("Enemy Texture: " + enemyRender.texture);
        }

        // Remove an entity
        entityManager.removeEntity(player.id);
    }
}

import java.util.Date;
import java.util.List;

public class Person {
    
    private String name;
    private int age;
    private List<String> hobbies;
    private Date timestamp;
    /**
     * Constructor for Person
     * @param name 
     * @param age
     * @param hobbies
     */
    public Person(String name, int age, List<String> hobbies) {
        this.name = name;
        this.age = age;
        this.hobbies = hobbies;
        this.timestamp = new Date();
    }
    
    /* Getters & Setters */
    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }

    public List<String> getHobbies() {
        return hobbies;
    }

    public Date gettimestamp() {
        return timestamp;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public void setHobbies(List<String> hobbies) {
        this.hobbies = hobbies;
    }

    public void settimestamp(Date timestamp) {
        this.timestamp = timestamp;
    }

    @Override
    public String toString() {
        return name + " (Age: " + age + ", Hobbies: " + hobbies + " " + timestamp + ")";
    }
}

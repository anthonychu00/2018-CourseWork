import java.util.*;
public class NameComparator implements Comparator<PersonNode>
{
    public int compare(PersonNode n1, PersonNode n2)
    {
        if(n1.getLastName().equals(n2.getLastName())&&n1.getFirstName().equals(n2.getFirstName()))
        return (new IdComparator()).compare(n1, n2);
        if(n1.getLastName().equals(n2.getLastName()))
        return n1.getFirstName().compareTo(n2.getFirstName());
        else
        return n1.getLastName().compareTo(n2.getLastName());
    }
}
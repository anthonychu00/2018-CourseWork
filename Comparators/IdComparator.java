import java.util.*;

public class IdComparator implements Comparator<PersonNode>
{
    public int compare(PersonNode n1, PersonNode n2)
    { 
        return n1.getIdNum().compareTo(n2.getIdNum());
    }
}
import java.util.*;
class PersonNode implements Comparable<PersonNode>
    {
        private String lastName;
        private String firstName;
        private String middleName;
        private String idNum;
        public PersonNode()
        {
            lastName=null;
            firstName=null;
            middleName=null;
            idNum=null;
        }
        public PersonNode(String last, String first, String middle, String id)
        {
            lastName=last;
            firstName=first;
            middleName=middle;
            idNum=id;
        }
        
        public String getLastName()
        {
            return lastName;
        }
        public String getFirstName()
        {
            return firstName;
        }
        public String getMiddleName()
        {
            return middleName;
        }
        public String getIdNum()
        {
            return idNum;
        }
        
        public int compareTo(PersonNode n1)
    { 
        return this.getIdNum().compareTo(n1.getIdNum());
    }
    
    /*public int compare(PersonNode n1, PersonNode n2)
    {
        if(n1.getLastName().equals(n2.getLastName())&&n1.getFirstName().equals(n2.getFirstName()))
        return (new IdComparator()).compare(n1, n2);
        if(n1.getLastName().equals(n2.getLastName()))
        return n1.getFirstName().compareTo(n2.getFirstName());
        else
        return n1.getLastName().compareTo(n2.getLastName());
    }*/
    }
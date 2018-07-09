import java.util.*;
public class TreeClient
{
    public static void main()
    {
        ArrayList<PersonNode> list =  new ArrayList<PersonNode>( );
        boolean g = false;
        list.add(new PersonNode("Marques","Paul","The-Great","123-45-678"));
        list.add(new PersonNode("Kent","Clark","Kriptonite","932-00-918"));
        list.add(new PersonNode("Luthor","Lex","King-of-Evil","632-95-174"));
        list.add(new PersonNode("Lane","Lois","Lipstick","390-29-4945"));
        list.add(new PersonNode("Bunny","Bugs","Hoppy","383-92-484"));
        list.add(new PersonNode("Duck","Daffy","Dippy","395-10-573"));
        list.add(new PersonNode("Flintstone","Fred","RockHead","592-96-285"));
        list.add(new PersonNode("Ruble","Barney","ShortStone","116-30-590"));
        list.add(new PersonNode("Flintstone","Wilma","Mary","883-95-499"));
        list.add(new PersonNode("Ruble","Betty","Boop","501-57-295"));
        list.add(new PersonNode("Man","Pac","Hungry","492-95-100"));
        list.add(new PersonNode("Invader","Space","1980sVideoGame","385-10-395"));
        list.add(new PersonNode("Bert","Q","-","385-19-305"));
        
        Tree t=new Tree();
        for(PersonNode w: list)
        {
            t.add(t.getHead(),w);
        }
    }
 
}
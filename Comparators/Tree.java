public class Tree
{
    TreeNode head;
    public Tree()
    {
        head=null;
    }
    
    private class TreeNode
    {
        private TreeNode left,right;
        private PersonNode value;
        public TreeNode()
        {
            left=null;
            right=null;
            value=null;
        }
        public TreeNode(PersonNode p)
        {
            value=p;
        }
        public PersonNode getValue()
    {
        return value;
    }
    }
    
    public void add(TreeNode h,PersonNode n)
    {
        if(head==null)
        {
            head=new TreeNode(n);
        }
        else if(h==null)
        {
            h=new TreeNode(n);
        }
        else if(n.getFirstName().compareTo(h.getValue().getFirstName())<=0)
        {
            add(h.left,n);
        }
        else if(n.getFirstName().compareTo(h.getValue().getFirstName())>0)
        {
            add(h.right,n);
        }
    }
    
    public TreeNode getHead()
    {
        return head;
    }

}
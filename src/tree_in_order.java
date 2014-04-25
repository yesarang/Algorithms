// Check out whether this code works properly at http://ideone.com/FAHPuT
/* package whatever; // don't place package name! */
import java.util.Stack;

class Ideone {
	static class Node { 
		private String value;
		private Node left;
		private Node right;
		static Node of(String value, Node left, Node right) {
			Node node = new Node();
			node.value = value;
			node.left = left;
			node.right = right;
			return node;
		}
	}
	
	static void inorderNonRecursion(Node tree) {
		Stack<Node> stack = new Stack<Node>();
		Node cur = null;
		stack.push(tree);
		while (!stack.isEmpty()) {
			cur = stack.peek();
			if (cur.left != null) {
				stack.push(cur.left);
			}
			else {
				while (!stack.isEmpty()) {
					cur = stack.pop();
					System.out.print(cur.value + " ");
					if (cur.right != null) {
						stack.push(cur.right);
						break;
					}
				}
			}
		}
		System.out.println("");
	}
	
	public static void main(String[] args) {
		Node tree = Node.of("root",
						Node.of("abc",
							Node.of("ghi", null, null),
							Node.of("pkl", null, null)),
						Node.of("def",
							Node.of("jkl", null, null),
							Node.of("orz", null, null)));
		
		inorderNonRecursion(tree);
		
		Node tree2 = Node.of("root",
						null,
						Node.of("def",
							null,
							Node.of("orz", null, null)));
		
		inorderNonRecursion(tree2);
		
		Node tree3 = Node.of("root",
						null,
						null);
		
		inorderNonRecursion(tree3);
		
		Node tree4 = Node.of("root",
						Node.of("def",
							Node.of("orz", null, null),
							null),
						null);
		
		inorderNonRecursion(tree4);
	}
}

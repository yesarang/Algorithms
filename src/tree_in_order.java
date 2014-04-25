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

	static class TraverseStatus {
		Node node;
		boolean leftComplete;
		boolean rightComplete;
		static TraverseStatus of(Node node, boolean leftComplete, boolean rightComplete) {
			TraverseStatus status = new TraverseStatus();
			status.node = node;
			status.leftComplete = leftComplete;
			status.rightComplete = rightComplete;
			
			return status;
		}
	}
	
	static void preorderNonRecursion(Node tree) {
		Stack<Node> stack = new Stack<Node>();
		Node cur = null;
		stack.push(tree);
		while (!stack.isEmpty()) {
			cur = stack.peek();
			System.out.print(cur.value + " ");

			if (cur.left != null) {
				stack.push(cur.left);
			}
			else {
				while (!stack.isEmpty()) {
					cur = stack.pop();
					if (cur.right != null) {
						stack.push(cur.right);
						break;
					}
				}
			}
		}
		System.out.println("");
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

	static void postorderNonRecursion(Node tree) {
		Stack<TraverseStatus> stack = new Stack<TraverseStatus>();
		Node cur = null;
		TraverseStatus status = null;
		stack.push(TraverseStatus.of(tree, false, false));
		while (!stack.isEmpty()) {
			status = stack.peek();
			cur = status.node;
			if (!status.leftComplete) {
				if (cur.left != null) {
					stack.push(TraverseStatus.of(cur.left, false, false));
				}
				else {
					status.leftComplete = true;
				}
			}
			else if (!status.rightComplete) {
				if (cur.right != null) {
					stack.push(TraverseStatus.of(cur.right, false, false));
				}
				else {
					status.rightComplete = true;
				}
			}
			else {
				System.out.print(cur.value + " ");
				stack.pop();
				if (!stack.isEmpty()) {
					TraverseStatus parentStatus = stack.peek();
					if (!parentStatus.leftComplete) {
						parentStatus.leftComplete = true;
					}
					else if (!parentStatus.rightComplete) {
						parentStatus.rightComplete = true;
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
		preorderNonRecursion(tree);
		postorderNonRecursion(tree);
		
		Node tree2 = Node.of("root",
						null,
						Node.of("def",
							null,
							Node.of("orz", null, null)));
		
		inorderNonRecursion(tree2);
		preorderNonRecursion(tree2);
		postorderNonRecursion(tree2);
		
		Node tree3 = Node.of("root",
						null,
						null);
		
		inorderNonRecursion(tree3);
		preorderNonRecursion(tree3);
		postorderNonRecursion(tree3);
		
		Node tree4 = Node.of("root",
						Node.of("def",
							Node.of("orz", null, null),
							null),
						null);
		
		inorderNonRecursion(tree4);
		preorderNonRecursion(tree4);
		postorderNonRecursion(tree4);
	}
}

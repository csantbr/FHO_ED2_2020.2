int recursiveFunction(No *tree, int buscado) {
	if(!tree) {
		return 0;
	} else if(tree->dado == buscado) {
		return 1;
	} else if(buscado > tree->dado) {
		return recursiveFunction(tree->right, buscado);
	} else if(buscado < tree->dado) {
		return recursiveFunction(tree->left, buscado);
	} else {
		return 0;
	}
}
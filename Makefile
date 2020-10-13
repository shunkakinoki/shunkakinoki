release:
	sed -i -e "s/^version = .*/version = \"$(VERSION)\"/" Cargo.toml

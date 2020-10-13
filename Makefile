release:
	version=$(node -pe "require('./package.json').version") \
	sed -i -e "s/^version = .*/version = \"$version\"/" Cargo.toml

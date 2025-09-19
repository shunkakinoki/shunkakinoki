.DEFAULT_GOAL := help

# ====================================================================================
# RESUME
# ====================================================================================

.PHONY: resume-docker-build
resume-docker-build:
	docker build -t shunkakinoki/resume .

.PHONY: resume
resume: resume-docker-build
	docker run --rm -v "$(CURDIR):/data" shunkakinoki/resume pdflatex resume.tex

.PHONY: resume-docker-run
resume-docker-run:
	@if [ -z "$(FILE)" ]; then \
		echo "Usage: make resume-docker-run FILE=path/to/your/resume.tex"; \
		exit 1; \
	fi; \
	$(MAKE) resume-docker-build
	docker run --rm -v "$(CURDIR):/data" shunkakinoki/resume pdflatex "$(FILE)"

# ====================================================================================
# HELP
# ====================================================================================

.PHONY: help
help: ## Show this help message.
	@echo "Usage: make <target>"
	@echo
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z0-9_-]+:.*?## / {printf "  \033[36m%-20s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST) 

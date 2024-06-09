# Source code location
SRCDIR  = src
# Compiled code location
CLSDIR  = bin

# Main class name
MAIN_CLASS = MainClass

# Compiler
JAVAC = javac

$(CLSDIR):
	mkdir -p $(CLSDIR)

.PHONY: clean run main

main: $(CLSDIR)
	$(JAVAC) -d $(CLSDIR) --source-path $(SRCDIR) $(SRCDIR)/$(MAIN_CLASS).java

clean:
	rm -rf $(CLSDIR)

run: main
	java -cp $(CLSDIR) $(MAIN_CLASS)

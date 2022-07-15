#include <maya/MPxCommand.h>

class ObjectsSelect : public MPxCommand {
public:
	ObjectsSelect() {}
	virtual ~ObjectsSelect() {}

	virtual MStatus doIt(const MArgList&);

	static void* creator() {
		return new ObjectsSelect();
	}

	static MSyntax cmdSyntax();
};
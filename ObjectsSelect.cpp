#include <maya/MGlobal.h>
#include <maya/MSyntax.h>
#include <maya/MFnDagNode.h>
#include <maya/mdagpath.h>
#include <maya/MSelectionList.h>
#include <maya/MItSelectionList.h>
#include <maya/MPlug.h>
#include <maya/MFnPlugin.h>
#include "ObjectsSelect.h"


MStatus ObjectsSelect::doIt(const MArgList& argList) {
	MDagPath node;
	MFnDagNode nodeFn;
    MObject component;
	MSelectionList list;
	MGlobal::getActiveSelectionList(list);

	MItSelectionList iter(list);
	
	if(iter.isDone()) {
		setResult("nothing selected");
		return MS::kSuccess;
	}

	for(; !iter.isDone(); iter.next()) {
		iter.getDagPath(node, component);
		nodeFn.setObject(node);
		auto result = nodeFn.name() + " is selected\n";
		setResult(result);
	}

	return MS::kSuccess;
}

MSyntax ObjectsSelect::cmdSyntax() {
	return MSyntax();
}

MStatus initializePlugin(MObject obj) {
	MFnPlugin plugin(obj, "Oz", "Any");

	auto status = plugin.registerCommand("Oselect", ObjectsSelect::creator, ObjectsSelect::cmdSyntax);

	if(!status) {
		status.perror("register cmd failed");
		return status;
	}
	return status;
}

MStatus uninitializePlugin(MObject obj) {
	MFnPlugin plugin(obj);
	auto status = plugin.deregisterCommand("Oselect");

	if(!status) {
		status.perror("failed to unload plugin");
		return status;
	}
	return status;
}



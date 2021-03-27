#include "plier/transforms/const_utils.hpp"

#include <mlir/IR/OpDefinition.h>
#include <mlir/IR/BuiltinTypes.h>

mlir::Attribute plier::getConstVal(mlir::Operation* op)
{
    assert(op);
    if (!op->hasTrait<mlir::OpTrait::ConstantLike>())
    {
        return {};
    }

    return op->getAttr("value");
}

mlir::Attribute plier::getConstVal(mlir::Value op)
{
    assert(op);
    if (auto parent_op = op.getDefiningOp())
    {
        return getConstVal(parent_op);
    }
    return {};
}

mlir::Attribute plier::getConstAttr(mlir::Type type, double val)
{
    assert(type);
    if (type.isa<mlir::FloatType>())
    {
        return mlir::FloatAttr::get(type, val);
    }
    if (type.isa<mlir::IntegerType, mlir::IndexType>())
    {
        return mlir::IntegerAttr::get(type, static_cast<int64_t>(val));
    }
    return {};
}

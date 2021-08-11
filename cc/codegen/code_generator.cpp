#include <codegen/code_generator.h>

namespace codegen {

    CodeGenerator::CodeGenerator(const std::string& programName)
    {
        m_context = std::make_unique<llvm::LLVMContext>();
        m_module = std::make_unique<llvm::Module>(programName, *m_context);
        m_builder = std::make_unique<llvm::IRBuilder<>>(*m_context);
    }

}
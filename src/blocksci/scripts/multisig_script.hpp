//
//  multisig_script.hpp
//  blocksci
//
//  Created by Harry Kalodner on 9/4/17.
//
//

#ifndef multisig_script_hpp
#define multisig_script_hpp

#include "scriptsfwd.hpp"
#include "script.hpp"

namespace blocksci {
    struct MultisigData;
    
    template <>
    class ScriptAddress<ScriptType::Enum::MULTISIG> : public Script {
        
    public:
        uint8_t required;
        uint8_t total;
        std::vector<Address> addresses;
        
        ScriptAddress<ScriptType::Enum::MULTISIG>(uint32_t scriptNum, const MultisigData *rawData);
        ScriptAddress<ScriptType::Enum::MULTISIG>(const ScriptAccess &access, uint32_t addressNum);
        
        std::string toString(const DataConfiguration &config) const override;
        std::string toPrettyString(const DataConfiguration &config, const ScriptAccess &access) const override;
        bool operator==(const Script &other) override;
        
        void visitPointers(const std::function<void(const Address &)> &visitFunc) const override {
            for (auto &address : addresses) {
                visitFunc(address);
            }
        }
        
#ifndef BLOCKSCI_WITHOUT_SINGLETON
        ScriptAddress<ScriptType::Enum::MULTISIG>(uint32_t addressNum);
#endif
    };
}


#endif /* multisig_script_hpp */

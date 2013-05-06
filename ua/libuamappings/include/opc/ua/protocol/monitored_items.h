/// @author Alexander Rykovanov 2013
/// @email rykovanov.as@gmail.com
/// @brief Monitored items services.
/// @license GNU LGPL
///
/// Distributed under the GNU LGPL License
/// (See accompanying file LICENSE or copy at
/// http://www.gnu.org/licenses/lgpl.html)
///

#ifndef OPC_UA_MAPPINGS_MONITORED_ITEMS_H_
#define OPC_UA_MAPPINGS_MONITORED_ITEMS_H_

#include <opc/ua/protocol/attribute.h>
#include <opc/ua/protocol/subscriptions.h>
#include <opc/ua/protocol/types.h>

namespace OpcUa
{
  enum class MonitoringMode : uint32_t
  {
    Disabled = 0,
    Sampling = 1,
    Reporting = 2,
  };

  enum class DataChangeTrigger : uint32_t
  {
    Status = 0,
    StatusAndValue = 1,
    StatusAndValueAndTimestamp = 2,
  };

  enum class DeadbandType : uint32_t
  {
    None = 0,
    Absolute = 1,
    Percent = 2,
  };

  struct DataChangeFilter
  {
    DataChangeTrigger Trigger;
    DeadbandType Deadband;
    double DeadbandValue;
  };

  struct SimpleAttributeOperand
  {
    NodeID TypeID;
    QualifiedName BrowsePath;
    IntegerID AttributeID;
    std::vector<std::string> IndexRange; // TODO ?
  };

  enum class FilterOperator
  {
    Equals = 0,
    IsNull = 1,
    GreaterThan = 2,
    LessThan = 3,
    GreaterThanOrEqual = 4,
    LessThanOrEqual = 5,
    Like = 6,
    Not = 7,
    Between = 8,
    InList = 9,
    And = 10,
    Or = 11,
    Cast = 12,
    BitwiseAnd = 16,
    BitwiseOr = 17,
  };

  struct ElementOperand
  {
    uint32_t Index;
  };

  struct LiteralAttribute
  {
    // BaseDataType Value; // TODO
  };

  struct AttributeOperand
  {
    NodeID Node;
    std::string Alias;
    RelativePath Path;
    IntegerID AttributeID;
    std::vector<std::string> IndexRange;
  };

  struct FilterOperand
  {
    NodeID TypeID;
    ElementOperand Element;
    AttributeOperand Attribute;
    SimpleAttributeOperand SimpleAttribute;
  };

  struct ContentFilter
  {
    FilterOperator Operator;
    std::vector<FilterOperand> FilterOperands;
  };

  struct EventFilter
  {
    std::vector<SimpleAttributeOperand> SelectClauses;
    ContentFilter WhereClause;
  };

  struct AggregateFilter
  {
    DateTime StartTime;
    NodeID AggregateType;
    Duration ProcessingInterval;
//    AggregateConfiguration Configuration;
    bool UseServerCapabilitiesDefaults;
    bool TreatUncertainAsBad;
    uint8_t PercentDataBad;
    uint8_t PercentDataGood;
    bool SteppedSlopedExtrapolation;
  };

  struct MonitoringFilter
  {
    ExtensionObjectHeader Header;
    DataChangeFilter DataChange;
    EventFilter Event;
    AggregateFilter Aggregate;
  };

  struct MonitoringParameters
  {
    IntegerID ClientHandle;
    Duration SamplingInterval;
    MonitoringFilter Filter;
    uint32_t QueueSize;
    bool DiscardOldest;
  };

  struct MonitoredItemRequest
  {
    AttributeValueID ItemToMonitor;
    MonitoringMode Mode;
    MonitoringParameters Parameters;
  };

  struct MonitoredItemsParameters
  {
    IntegerID SubscriptionID;
    TimestampsToReturn Timestamps;
    std::vector<MonitoredItemRequest> ItemsToCreate;
  };

  struct CreateMonitoredItemsRequest
  {
    NodeID TypeID;
    RequestHeader Header;
    MonitoredItemsParameters Parameters;

    CreateMonitoredItemsRequest();
  };

  ///////////////////////////////////////////////////////////////////////

  struct MonitoredItemsData
  {
    // TODO: place Results into a struct
    // TODO: replace uint8_t with MonitoredItemsResult
    // TODO: result contain a vector, I will response with empty container
    std::vector<uint8_t> Results;
    std::vector<DiagnosticInfo> Infos;
  };

  struct CreateMonitoredItemsResponse
  {
    NodeID TypeID;
    ResponseHeader Header;
    MonitoredItemsData Data;

    CreateMonitoredItemsResponse();
  };

}

#endif // OPC_UA_MAPPINGS_MONITORED_ITEMS_H_

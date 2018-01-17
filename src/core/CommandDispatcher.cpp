#include <Poco/Logger.h>

#include "core/CommandDispatcher.h"

using namespace BeeeOn;
using namespace Poco;

CommandDispatcher::~CommandDispatcher()
{
}

void CommandDispatcher::registerHandler(SharedPtr<CommandHandler> handler)
{
	for (auto &item : m_commandHandlers) {
		if (item == handler)
			throw Poco::ExistsException("duplicate handler detected");
	}

	m_commandHandlers.push_back(handler);
}

void CommandDispatcher::injectImpl(Answer::Ptr answer, SharedPtr<AnswerImpl> impl)
{
	answer->installImpl(impl);
}

void CommandDispatcher::registerListener(CommandDispatcherListener::Ptr listener)
{
	m_eventSource.addListener(listener);
}

void CommandDispatcher::dispatch(Command::Ptr cmd, Answer::Ptr answer)
{
	notifyDispatch(cmd);

	logger().debug(cmd->toString(), __FILE__, __LINE__);

	dispatchImpl(cmd, answer);
}

void CommandDispatcher::notifyDispatch(Command::Ptr cmd)
{
	m_eventSource.fireEvent(cmd, &CommandDispatcherListener::onDispatch);
}

void CommandDispatcher::setExecutor(Poco::SharedPtr<AsyncExecutor> executor)
{
	m_eventSource.setAsyncExecutor(executor);
}

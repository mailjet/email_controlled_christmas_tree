Mailjet.configure do |config|
  config.api_key = ENV['mailjetApiKey']
  config.secret_key = ENV['mailjetSecretKey']
  config.default_from = ENV['mailjetDefaultFrom']
end
